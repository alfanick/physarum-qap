#!/usr/bin/python

import matplotlib.pyplot
import argparse
from os.path import basename
import os

def avg(a):
    return float(sum(a))/len(a)

class Dataset:
    def __init__(self, log):
        self.name = basename(log.name)
        self.timeline = self.parse_log(log)
        self.plasmodia = self.group_plasmodia(self.timeline)

    def parse_log(self, log):
        timeline = []

        previous_f = {}
        for line in log.readlines():
            f = dict(field.split('=') for field in line.rstrip().split(' '))

            for (k, v) in f.iteritems():
                if '.' in v:
                    v = float(v)
                else:
                    try:
                        v = int(v)
                    except:
                        pass

                f[k] = v

            if f['plasmodium'] != '*':
                temp_f = previous_f.copy()
                temp_f.update(f)
                f = temp_f

            previous_f = f

            timeline.append(f)

        log.close()
        return timeline

    def group_plasmodia(self, timeline):
        plasmodia = {}

        for entry in timeline:
            if entry['plasmodium'] not in plasmodia:
                plasmodia[entry['plasmodium']] = []

            plasmodia[entry['plasmodium']].append(entry)

        return plasmodia


class PlotGenerator:
    def __init__(self, datasets):
        self.datasets = datasets

    def multiple_instance_aggregated_key(self, key, aggregate, label=None,
                                         states=('crawling',),
                                         title=True, legend=True):
        figure, plt = matplotlib.pyplot.subplots()

        plt.set_axisbelow(True)
        figure.set_size_inches((18, 6), forward=True)
        plt.grid(b=True, which='major', color='lightgray', linestyle='-')
        plt.grid(b=True, which='minor', color='whitesmoke', linestyle='-')
        plt.minorticks_on()

        max_epoch = 0

        for dataset in self.datasets:
            local_max_epoch = 0
            data = {}

            for entry in dataset.plasmodia['*']:
                if entry['epoch'] > local_max_epoch:
                    local_max_epoch = entry['epoch']

                if entry['epoch'] not in data:
                    data[entry['epoch']] = []

            if local_max_epoch > max_epoch:
                max_epoch = local_max_epoch

            for name in dataset.plasmodia:
                if isinstance(name, int):
                    for entry in dataset.plasmodia[name]:
                        if entry['state'] in states:
                            data[entry['epoch']].append(entry[key])

            aggregated_data = []

            for epoch, values in data.iteritems():
                if len(values) > 0:
                    aggregated_data.append(aggregate(values))

            plt.plot(aggregated_data, label=dataset.name)

        if label is None:
            label = key

        plt.set_ylabel(label)
        plt.set_xlabel('epoch')
        plt.set_xlim(right=max_epoch)
        x1, x2, y1, y2 = plt.axis()

        if y1 < 10 and y2 > 1.5:
            plt.axis((x1, x2, 0, y2*1.01))

        if legend:
            plt.legend()

        if title is True:
            plt.set_title("%s aggregated %s - %s" %
                            (key, aggregate.__name__, dataset.name))
        elif isinstance(title, basestring):
            plt.set_title(title)


        return [figure]


    def multiple_instance_single_key(self, key, label=None, title=True,
                                     legend=True):
        figure, plt = matplotlib.pyplot.subplots()

        plt.set_axisbelow(True)
        figure.set_size_inches((18, 6), forward=True)
        plt.grid(b=True, which='major', color='lightgray', linestyle='-')
        plt.grid(b=True, which='minor', color='whitesmoke', linestyle='-')
        plt.minorticks_on()

        max_epoch = 0

        for dataset in self.datasets:
            data = []

            for entry in dataset.plasmodia['*']:
                if entry['epoch'] > max_epoch:
                    max_epoch = entry['epoch']

                if key in entry:
                    data.append(entry[key])

            plt.plot(data, label=dataset.name)

        if label is None:
            label = key

        plt.set_ylabel(label)
        plt.set_xlabel('epoch')
        plt.set_xlim(right=max_epoch)
        x1, x2, y1, y2 = plt.axis()

        if y1 < 10 and y2 > 1.5:
            plt.axis((x1, x2, 0, y2*1.01))

        if legend:
            plt.legend()

        if title is True:
            plt.set_title("%s - %s" %
                            (key, dataset.name))
        elif isinstance(title, basestring):
            plt.set_title(title)


        return [figure]


    def single_instance_plasmodia_state(self):
        plots = []

        for dataset in self.datasets:
            max_epoch = dataset.plasmodia['*'][-1]['epoch']
            figure, plt = matplotlib.pyplot.subplots()

            plt.set_axisbelow(True)
            figure.set_size_inches((18, 6), forward=True)
            plt.grid(b=True, which='major', color='lightgray', linestyle='-')

            alive = []
            dead = []
            merge = []

            delta_dead = 0
            delta_alive = 0
            delta_merge = 0

            for entry in dataset.timeline:
                if entry['plasmodium'] == '*':
                    if entry['epoch'] > 0:
                        alive.append(delta_alive)
                        dead.append(delta_dead)
                        merge.append(delta_merge)
                else:
                    if entry['state'] == 'dead':
                        delta_dead += 1
                        delta_alive -= 1
                    elif entry['state'] == 'merge':
                        delta_alive -= 1
                        delta_merge += 1
                    elif entry['state'] == 'new':
                        delta_alive += 1

            plt.plot(alive, label='alive')
            plt.plot(dead, label='dead')
            plt.plot(merge, label='merged')
            plt.set_ylabel('number of plasmodia')
            plt.set_xlabel('epoch')
            plt.set_xlim(right=max_epoch)
            plt.legend()

            x1, x2, y1, y2 = plt.axis()
            plt.axis((x1, x2, y1, y2+1))

            plt.set_title("state of colony - %s" % dataset.name)

            plots.append(figure)


        return plots


    def single_instance_multiple_plasmodia(self, key, states=('crawling',),
                                           label=None, title=True,
                                           legend=False):
        plots = []

        for dataset in self.datasets:
            max_epoch = dataset.plasmodia['*'][-1]['epoch']
            figure, plt = matplotlib.pyplot.subplots()
            plt.set_axisbelow(True)

            figure.set_size_inches((18, 6), forward=True)
            plt.grid(b=True, which='major', color='lightgray', linestyle='-')
            plt.grid(b=True, which='minor', color='whitesmoke', linestyle='-')
            plt.minorticks_on()

            names = filter(lambda x: isinstance(x, int),
                           dataset.plasmodia.keys())

            for name in names:
                data = []

                for entry in dataset.plasmodia[name]:
                    if entry['state'] in states:
                        data.append(entry[key])

                plt.plot(data, label="#%i" % name)

            if label is None:
                label = key

            plt.set_ylabel(label)
            plt.set_xlabel('epoch')
            plt.set_xlim(right=max_epoch)
            x1, x2, y1, y2 = plt.axis()

            if y1 < 10 and y2 > 1.5:
                plt.axis((x1, x2, 0, y2*1.01))

            if legend:
                plt.legend()

            if title is True:
                plt.set_title("%s for each plasmodium - %s" %
                              (key, dataset.name))
            elif isinstance(title, basestring):
                plt.set_title(title)

            plots.append(figure)

        return plots



if __name__ == '__main__':
    matplotlib.pyplot.rc('text', usetex=True)
    matplotlib.pyplot.rc('font', family='serif')

    parser = argparse.ArgumentParser(description="Charts generator")

    parser.add_argument('-l', '--log', type=argparse.FileType('r'),
                        required=True, nargs='+')

    parser.add_argument('-o', '--out', type=str, required=True)

    args = parser.parse_args()
    if not os.path.exists(args.out):
        os.makedirs(args.out)

    datasets = map(Dataset, args.log)

    generator = PlotGenerator(datasets)

    f = []

    f += generator.multiple_instance_single_key('total_food_eaten_count',
                                                label='number of visited solutions')

    f += generator.multiple_instance_single_key('memory',
                                                label='total memory usage')

    f += generator.multiple_instance_single_key('time',
                                                label='execution time')

    f += generator.multiple_instance_single_key('solution_cost',
                                                label='cost of best solution')

    f += generator.single_instance_plasmodia_state()

    detailed = {'food': (('new', 'crawled'), 'plasmodium energy'),
                'size': (('new', 'crawled', 'dead'), 'number of occupied solutions'),
                'total_explored': (('new', 'crawled'), 'total number of explored solutions'),
                'total_crawled': (('new', 'crawled'), 'total number of crawled solutions'),
                'frontier': (('crawled', 'merged'), 'number of solutions in frontier'),
                'frontier_best_cost': (('crawled',), 'cost of best solution in frontier'),
                'frontier_worst_cost': (('crawled',), 'cost of worst solution in frontier')}

    aggregates = (min, max, sum, avg)

    for key, conf in detailed.iteritems():
        f += generator.single_instance_multiple_plasmodia(key, states=conf[0],
                                                          label=conf[1])

        for agg in aggregates:
            f += generator.multiple_instance_aggregated_key(key, agg,
                                                            states=conf[0],
                                                            label=conf[1])

    for plot in f:
        filename = plot.gca().title.get_text()
        plot.gca().title.set_visible(False)

        plot.savefig("%s/%s.pdf" % (args.out, filename),
                     bbox_inches='tight')

        plot.gca().set_xlim(0, 0.2 * plot.gca().get_xlim()[1])
        plot.savefig("%s/%s.zoomed.pdf" % (args.out, filename),
                     bbox_inches='tight')

        plot.gca().set_xlim(0, 0.25 * plot.gca().get_xlim()[1])
        plot.savefig("%s/%s.zzzoomed.pdf" % (args.out, filename),
                     bbox_inches='tight')
