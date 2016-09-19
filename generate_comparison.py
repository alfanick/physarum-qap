#!/usr/bin/python

import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot
import argparse
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

    for idx, baseline_solution in enumerate(baseline):
        print(baseline_solution.name)

        for group_name, solutions in groups_without_baseline.iteritems():
            print("  " + group_name)
            print(solutions[idx].distance(baseline_solution))
            print(solutions[idx].similarity(baseline_solution))

