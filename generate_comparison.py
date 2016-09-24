#!/usr/bin/python

import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot
import copy
import argparse
import numpy as np
from os.path import basename
import os
import sys
import csv


class Solution:
    def __init__(self, sln):
        self.name = os.path.splitext(basename(sln.name))[0]
        self.cost, self.size, self.assignment = self.parse_solution(sln)
        self.instance = 0
        self.aggregated = False

    def parse_solution(self, sln):
        numbers = [int(v) for v in sln.read().split()]

        size = numbers[0]
        cost = numbers[1]
        assignment = numbers[2:]

        return (cost, size, assignment)

    def __repr__(self):
        return "%s = %d" % (self.name, self.cost)

    def distance(self, baseline):
        return float(self.cost - baseline.cost) / baseline.cost

    def similarity(self, baseline):
        same = 0

        for idx, value in enumerate(baseline.assignment):
            if value == self.assignment[idx]:
                same += 1

        return float(same) / len(baseline.assignment)


class PlotGenerator:
    COLORS = ['b', 'g', 'r', 'c', 'm', 'y']

    def __init__(self, baseline, groups):
        self.baseline = baseline
        self.groups = groups

    def bar_chart(self, comparator, title, label, exclude_avg=False):
        figure, plt = matplotlib.pyplot.subplots()

        plt.set_axisbelow(True)
        plt.yaxis.grid(b=True, which='major', color='lightgray', linestyle='-')

        data = {}
        lgnd = {}

        width = 1.0/(len(self.groups) + 2)
        i = 0

        gnames = sorted(self.groups.keys(), reverse=True)

        for group_name in gnames:
            solutions = self.groups[group_name]
            if exclude_avg and group_name.endswith('_avg'):
                continue

            data[group_name] = {}

            for idx, baseline_solution in enumerate(self.baseline):
                data[group_name][baseline_solution.name] = comparator(solutions[idx], baseline_solution)

            values = [data[group_name][k] for k in sorted(data[group_name])]
            c = self.COLORS[i%len(self.COLORS)]

            if group_name.endswith('avg'):
                c = 'b'
            elif group_name.endswith('min'):
                c = 'g'
            elif group_name.endswith('max'):
                c = 'r'


            b = plt.bar(np.arange(len(solutions)) + i * width, values, width,
                        color = c)
            i += 1
            lgnd[b[0]] = group_name

        plt.set_title(title)
        plt.set_xlabel('dataset')
        plt.set_ylabel(label)
        plt.set_xticklabels([v.name for v in self.baseline], rotation=45)
        plt.set_xticks(np.arange(len(self.baseline)) + width)

        plt.legend(sorted(lgnd.keys(), key=lambda x: lgnd[x], reverse=True),
                sorted(lgnd.values(), reverse=True), loc='best')

        return [figure]

    def multiple_instance_distance(self):
        return self.bar_chart(lambda a,b: a.distance(b),
                              title='distance',
                              label='relative error')


    def multiple_instance_similarity(self):
        return self.bar_chart(lambda a,b: a.similarity(b),
                             title='similarity',
                             label='fraction of correct assignment',
                             exclude_avg=True)

if __name__ == '__main__':
    matplotlib.pyplot.rcParams['backend'] = 'TkAgg'
    matplotlib.pyplot.rcParams['agg.path.chunksize'] = 100000
    # matplotlib.pyplot.rc('text', usetex=True)
    matplotlib.pyplot.rc('font', family='serif')

    parser = argparse.ArgumentParser(description="Comparison charts generator")

    parser.add_argument('-s', '--solution', type=argparse.FileType('r'),
                        required=True, nargs='+')
    parser.add_argument('-b', '--baseline', type=str,
                        default='qapdatsol')
    parser.add_argument('-o', '--out', type=str, required=True)
    parser.add_argument('-f', '--format', type=str, default='png')
    parser.add_argument('-a', '--aggregate', action='store_true')
    parser.set_defaults(aggregate=False)

    args = parser.parse_args()
    if not os.path.exists(args.out):
        os.makedirs(args.out)

    groups = {}

    for f in args.solution:
        path, name = os.path.split(f.name)
        path, group_name = os.path.split(path)

        if group_name not in groups:
            groups[group_name] = []

        try:
            groups[group_name].append(Solution(f))
        except:
            print("skipping %s" % f.name)

    if args.baseline not in groups:
        print('No baseline given')
        sys.exit(-1)

    if args.aggregate:
        aggregated_groups = {}
        report = []
        name_vs_instances = {}

        for group_name in groups:
            if group_name != args.baseline:
                avg_name = group_name + "_avg"
                min_name = group_name + "_min"
                max_name = group_name + "_max"

                for n in (avg_name, min_name, max_name):
                    aggregated_groups[n] = []

                instances = {}
                for solution in groups[group_name]:
                    (name, instance) = solution.name.split('.')

                    if name not in instances:
                        instances[name] = []

                    if name not in name_vs_instances:
                        name_vs_instances[name] = []

                    solution.name = name
                    solution.instance = int(instance)
                    instances[name].append(solution)
                    name_vs_instances[name].append(solution)

                for instance_name, solutions in instances.iteritems():
                    aggregated_groups[min_name].append(min(solutions, key=lambda x: x.cost))
                    aggregated_groups[max_name].append(max(solutions, key=lambda x: x.cost))

                    s = copy.copy(solutions[0])
                    sum_cost = 0

                    for solution in solutions:
                        sum_cost += solution.cost

                    s.cost = float(sum_cost) / len(solutions)
                    aggregated_groups[avg_name].append(s)


        best_header = ['name', 'cost_{optimal}', 'size', 'cost_{min}',
                'dist_{min}', 'sim_{min}', 'cost_{1}', 'cost_{2}', 'cost_{3}',
                'cost_{4}', 'cost_{5}', 'cost_{6}', 'cost_{7}', 'cost_{8}',
                'cost_{9}', 'cost_{10}', 'cost_{avg}']
        rows = []

        for name in name_vs_instances:
            opt = filter(lambda x: x.name == name, groups[args.baseline])[0]

            row = {'name': name,
                   'cost_{optimal}': opt.cost,
                   'size': len(opt.assignment)}

            min_instance = None
            s = 0

            for idx, instance in enumerate(name_vs_instances[name]):
                row["cost_{%d}" % (idx+1)] = instance.cost
                s += instance.cost

                if min_instance is None or instance.cost < min_instance.cost:
                    min_instance = instance

            row['cost_{avg}'] = s / len(name_vs_instances[name])
            row['cost_{min}'] = min_instance.cost
            row['dist_{min}'] = min_instance.distance(opt)
            row['sim_{min}'] = min_instance.similarity(opt)

            for idx in range(0, 10):
                name = "cost_{%d}" % (idx+1)

                if not name in row:
                    row[name] = None

            rows.append(row)

        with open("%s/data.csv" % args.out, 'w') as f:
            writer = csv.DictWriter(f, fieldnames=best_header)
            # writer.writeheader()

            for r in sorted(rows, key=lambda x: x['name']):
                writer.writerow(r)

        aggregated_groups[args.baseline] = groups[args.baseline]
        groups = aggregated_groups

    for gn in groups:
        groups[gn] = sorted(groups[gn], key=lambda x: x.name)

    groups_without_baseline = dict((i,groups[i]) for i in groups if i != args.baseline)
    baseline = groups[args.baseline]

    generator = PlotGenerator(baseline, groups_without_baseline)

    f = []

    f += generator.multiple_instance_distance()
    f += generator.multiple_instance_similarity()

    for plot in f:
        filename = plot.gca().title.get_text()
        plot.gca().title.set_visible(False)

        plot.savefig("%s/%s.%s" % (args.out, filename, args.format),
                     bbox_inches='tight', dpi=150)

        plot.clf()

