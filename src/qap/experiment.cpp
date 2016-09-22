#include "./experiment.hpp"

#ifdef LOG
#include "../external/getRSS.h"
#endif

#include <queue>
#include <cassert>
#include <set>
#include <algorithm>

#define BATCH_SIZE 10000

namespace PUT {
namespace Physarum {

Experiment::Experiment(const Environment &e, size_t ss, size_t ips, bool sm) : environment(e), sample_size(ss), initial_population_size(ips), should_merge(sm) {
  // population must be smaller than number of samples
  assert(ips <= ss);

  // sample solutions
  std::priority_queue<Solution> samples;

#ifdef LOG
    std::cerr << "plasmodium=* epoch=0" << std::endl;
#endif

  std::vector<Solution> subsamples;
  size_t number_of_samples = 0;
  subsamples.reserve(BATCH_SIZE);

  // create samples
  for (size_t batch = 0; batch <= ss / BATCH_SIZE; batch++) {
    subsamples.clear();

    for (size_t i = 0; i < BATCH_SIZE; i++) {
      subsamples.emplace_back(environment.getProblem());

      number_of_samples++;
      if (number_of_samples > ss)
        break;
    }

    std::sort(subsamples.rbegin(), subsamples.rend());
    for (size_t i = 0; i < ips && i < subsamples.size(); i++) {
      samples.push(subsamples[i]);
    }
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
  Solution best_solution(environment.getProblem());

  for (auto& plasmodium : population) {
    Solution best_local(environment.getProblem());

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

Solution Experiment::getHistoricalSolution() {
  Solution best_solution(environment.getProblem());
  float bhc = best_solution.cost();

  for (auto& plasmodium : population) {
    if (plasmodium.best_historical_cost < bhc) {
      best_solution = plasmodium.best_historical_solution;
      bhc = plasmodium.best_historical_cost;
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
    std::cerr << "plasmodium=* epoch=" << epoch+1 <<" time=" << time(0) - start_time << " memory=" << getCurrentRSS() << " total_food_eaten_count=" << environment.getFoodEatenCount() << " solution_cost=" << getSolution().cost() << std::endl;
#endif

    for (auto& plasmodium : population) {
      if (plasmodium.isAlive()) {
        plasmodium.explore();
        plasmodium.crawl();
        is_alive = true;
      }
    }

    if (should_merge) {
      merge();
    }

    epoch++;

    if (time(0) - start_time >= max_time)
      break;
  }

#ifdef LOG
    std::cerr << "plasmodium=* epoch=" << epoch+1 <<" time=" << time(0) - start_time << " memory=" << getCurrentRSS() << " total_food_eaten_count=" << environment.getFoodEatenCount() << " solution_cost=" << getSolution().cost() << std::endl;
#endif
}

  void Experiment::merge() {
    for (auto& plasmodium : population) {
      for (auto& other_plasmodium : population) {
        if (plasmodium.id == other_plasmodium.id ||
            !plasmodium.alive ||
            !other_plasmodium.alive) {
          continue;
        }

        std::set<Solution> out;

        std::set_intersection(plasmodium.occupancy.begin(), plasmodium.occupancy.end(), other_plasmodium.occupancy.begin(), other_plasmodium.occupancy.end(), std::inserter(out, out.begin()));

        if (out.empty()) {
          continue;
        }

        out.clear();

        std::set_union(plasmodium.occupancy.begin(), plasmodium.occupancy.end(), other_plasmodium.occupancy.begin(), other_plasmodium.occupancy.end(), std::inserter(out, out.begin()));

        plasmodium.occupancy.clear();
        std::copy(out.begin(), out.end(), std::back_inserter(plasmodium.occupancy));


        plasmodium.initial_food += other_plasmodium.initial_food;
        plasmodium.food = 0.0;

        for (auto& solution : plasmodium.occupancy) {
          plasmodium.food += environment.getFood(solution);
        }

        plasmodium.explored_count += other_plasmodium.explored_count;
        plasmodium.crawled_count += other_plasmodium.crawled_count;

        other_plasmodium.alive = false;
        other_plasmodium.frontier.clear();
        other_plasmodium.occupancy.clear();
        plasmodium.frontier.clear();

        if (other_plasmodium.best_historical_cost < plasmodium.best_historical_cost) {
          plasmodium.best_historical_cost = other_plasmodium.best_historical_cost;
          plasmodium.best_historical_solution = other_plasmodium.best_historical_solution;
        }
#ifdef LOG
    std::cerr << "plasmodium=" << plasmodium.id << " state=merge with=" << other_plasmodium.id << " food=" << plasmodium.food << " size=" << plasmodium.occupancy.size() << " frontier=0 total_explored=" << plasmodium.explored_count << " total_crawled=" << plasmodium.crawled_count << std::endl;
#endif
      }
    }
  }

}
}
