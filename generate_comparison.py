#!/usr/bin/python

import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot
import argparse
import numpy as np
from os.path import basename
import os
import sys


class Solution:
    def __init__(self, sln):
        self.name = os.path.splitext(basename(sln.name))[0]
        self.cost, self.size, self.assignment = self.parse_solution(sln)

    def parse_solution(self, sln):
        numbers = [int(v) for v in sln.read().split()]

        size = numbers[0]
        cost = numbers[1]
        assignment = numbers[2:-1]

        return (cost, size, assignment)

    def __repr__(self):
        return self.name

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

    def bar_chart(self, comparator, title, label):
        figure, plt = matplotlib.pyplot.subplots()

        plt.set_axisbelow(True)
        plt.yaxis.grid(b=True, which='major', color='lightgray', linestyle='-')

        data = {}
        lgnd = {}

        width = 1.0/(len(self.groups) + 2)
        i = 0

        for group_name, solutions in self.groups.iteritems():
            data[group_name] = {}

            for idx, baseline_solution in enumerate(self.baseline):
                data[group_name][baseline_solution.name] = comparator(solutions[idx], baseline_solution)

            values = [data[group_name][k] for k in sorted(data[group_name])]
            b = plt.bar(np.arange(len(solutions)) + i * width, values, width,
                        color = self.COLORS[i%len(self.COLORS)])
            i += 1
            lgnd[b[0]] = group_name

        plt.set_title(title)
        plt.set_xlabel('dataset')
        plt.set_ylabel(label)
        plt.set_xticklabels([v.name for v in self.baseline], rotation=45)
        plt.set_xticks(np.arange(len(self.baseline)) + width)

        plt.legend(lgnd.keys(), lgnd.values(), loc='best')

        return [figure]

    def multiple_instance_distance(self):
        return self.bar_chart(lambda a,b: a.distance(b),
                              title='distance',
                              label='relative error')


    def multiple_instance_similarity(self):
        return self.bar_chart(lambda a,b: a.similarity(b),
                             title='similarity',
                             label='fraction of correct assignment')

if __name__ == '__main__':
    matplotlib.pyplot.rcParams['backend'] = 'TkAgg'
    matplotlib.pyplot.rcParams['agg.path.chunksize'] = 100000
    matplotlib.pyplot.rc('text', usetex=True)
    matplotlib.pyplot.rc('font', family='serif')

    parser = argparse.ArgumentParser(description="Comparison charts generator")

    parser.add_argument('-s', '--solution', type=argparse.FileType('r'),
                        required=True, nargs='+')
    parser.add_argument('-b', '--baseline', type=str,
                        default='qapdatsol')
    parser.add_argument('-o', '--out', type=str, required=True)
    parser.add_argument('-f', '--format', type=str, default='png')

    args = parser.parse_args()
    if not os.path.exists(args.out):
        os.makedirs(args.out)

    groups = {}

    for f in args.solution:
        path, name = os.path.split(f.name)
        path, group_name = os.path.split(path)

        if group_name not in groups:
            groups[group_name] = []

        groups[group_name].append(Solution(f))

    for gn in groups:
        groups[gn] = sorted(groups[gn], key=lambda x: x.size)

    if args.baseline not in groups:
        print('No baseline given')
        sys.exit(-1)

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

