#include "./experiment.hpp"

#ifdef LOG
#include "../external/getRSS.h"
#endif

#include <queue>
#include <cassert>

namespace PUT {
namespace Physarum {

Experiment::Experiment(const Environment &e, size_t ss, size_t ips) : environment(e), sample_size(ss), initial_population_size(ips) {
  // population must be smaller than number of samples
  assert(ips <= ss);

  // sample solutions
  std::priority_queue<Solution> samples;

#ifdef LOG
    std::cerr << "plasmodium=* epoch=0" << std::endl;
#endif

  // create samples
  for (size_t i = 0; i < ss; i++) {
    samples.emplace(&environment.getProblem());
  }

  // best cost
  environment.calibrate(samples.top().cost());

  // put plasmodium on best samples
  for (size_t i = 0; i < ips; i++) {
    auto& sample = samples.top();

    population.emplace_back(&environment, sample, environment.getInitialFood());
    samples.pop();
  }
}

Solution Experiment::getSolution() {
  Solution best_solution(&environment.getProblem());

  for (auto& plasmodium : population) {
    Solution best_local(&environment.getProblem());

    for (auto& solution : plasmodium.getPositions()) {
      if (solution.cost() < best_local.cost()) {
        best_local = solution;
      }
    }

    if (best_local.cost() < best_solution.cost()) {
      best_solution = best_local;
    }

  }

  return best_solution;
}

void Experiment::run(unsigned int max_time) {
  size_t epoch = 0;
  unsigned int start_time = time(0);
  bool is_alive = true;

  while (is_alive) {
    is_alive = false;

#ifdef LOG
    std::cerr << "plasmodium=* epoch=" << epoch+1 << " memory=" << getCurrentRSS() << std::endl;
#endif

    for (auto& plasmodium : population) {
      if (plasmodium.isAlive()) {
        plasmodium.explore();
        plasmodium.crawl();
        is_alive = true;
      }
    }

    // merge()

    if (epoch % 100 == 0) {
      if (time(0) - start_time >= max_time)
        break;
    }

    epoch++;
  }
}

}
}
