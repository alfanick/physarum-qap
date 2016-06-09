#include "./experiment.hpp"

#include <queue>

namespace PUT {
namespace Physarum {

Experiment::Experiment(const Environment &e, size_t ss, size_t ips) : environment(e), sample_size(ss), initial_population_size(ips) {
  // sample solutions
  std::priority_queue<Solution> samples;

  // create samples
  for (size_t i = 0; i < ss; i++) {
    samples.emplace(&environment.getProblem());
  }

  // best cost
  environment.calibrate(samples.top().cost());

  // put plasmodium on best samples
  for (size_t i = 0; i < ips; i++) {
    auto& sample = samples.top();

    population.emplace_back(&environment, sample, environment.getInitialFood(sample));
    samples.pop();
  }
}

Solution Experiment::getSolution() {
  Solution best_solution(&environment.getProblem());

  for (auto& plasmodium : population) {
    Solution best_local(&environment.getProblem());
    for (auto& solution : plasmodium.getPositions()) {
      if (solution.cost() < best_solution.cost()) {
        best_solution = solution;
      }

      if (solution.cost() < best_local.cost()) {
        best_local = solution;
      }
    }

    std::cerr << plasmodium.getId() << " " << environment.getInitialFood(best_local) << " " << plasmodium.getPositions().size() << " " << plasmodium.getExploredCount() << " " << plasmodium.getCrawledCount() << std::endl;
  }
  std::cerr << std::endl;

  return best_solution;
}

void Experiment::run(unsigned int max_time) {
  size_t epoch = 0;
  unsigned int start_time = time(0);

  while (true) {
    for (auto& plasmodium : population) {
      plasmodium.explore();
      plasmodium.crawl();
    }

    // merge()

    if (epoch % 100 == 0) {
      std::cerr << "Epoch: " << epoch << std::endl;
      if (time(0) - start_time >= max_time)
        break;
    }

    epoch++;
  }
}

}
}
