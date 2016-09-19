#include "./plasmodium.hpp"
#include <algorithm>

namespace PUT {
namespace Physarum {

Plasmodium::Plasmodium(Environment* e, Solution position, float i) : initial_food(i), environment(e), best_historical_solution(Solution(&(e->getProblem()))) {
  id = next_id();
  size = position.assignment.size();
  explored_count = 0;
  crawled_count = 0;
  occupancy.push_back(position);
  food = initial_food + e->getFood(position);
  alive = true;
  best_historical_cost = best_historical_solution.cost();

#ifdef LOG
  std::cerr << "plasmodium=" << id << " state=new food=" << food << " cost=" << position.cost() << " size=1 frontier=0 total_explored=0 total_crawled=0" << std::endl;
#endif
}

void Plasmodium::explore() {
  float explore_cost = environment->getExploreCost();
  frontier.clear();

#ifdef LOG
    std::cerr << "plasmodium=" << id << " state=exploring food=" << food << " size=" << occupancy.size() << " frontier=0 total_explored=" << explored_count << " total_crawled=" << crawled_count << std::endl;
#endif

  // try to move
  while (food > (environment->getCrawlCost() + occupancy.size() * environment->getExploreCost())) {
    // find next node
    size_t a = rand() % size;
    size_t b = a;

    while (a == b)
      b = rand() % size;

    for (auto solution : occupancy) {
      if (initial_food >= explore_cost) {
        initial_food -= explore_cost;
      } else {
        environment->eatFood(solution, explore_cost);
      }

      food -= explore_cost;

      std::swap(solution.assignment[a], solution.assignment[b]);

      if (environment->getFood(solution) <= 0) {
        continue;
      }

      frontier.push_back(solution);
      explored_count++;
    }

  }

#ifdef LOG
    // not used, same as crawl
    // std::cerr << "plasmodium=" << id << " state=explored food=" << food << " size=" << occupancy.size() << " frontier=" << frontier.size() << " total_explored=" << explored_count << " total_crawled=" << crawled_count << std::endl;
#endif
}

void Plasmodium::crawl() {
  if (frontier.empty()) {
    alive = false;
#ifdef LOG
    std::cerr << "plasmodium=" << id << " state=dead food=" << food << " size=" << occupancy.size() << " frontier=0 total_explored=" << explored_count << " total_crawled=" << crawled_count << std::endl;
#endif
    return;
  }

  std::sort(frontier.begin(), frontier.end(), [&](const Solution& a,  const Solution& b) {
    return environment->getFood(a) > environment->getFood(b);
  });

  float c = frontier.front().cost();
  if (c < best_historical_cost) {
    best_historical_solution = frontier.front();
    best_historical_cost = c;
   }

  if (environment->getFood(frontier.front()) > (environment->getCrawlCost() + environment->getExploreCost())) {
#ifdef LOG
    std::cerr << "plasmodium=" << id << " state=crawling food=" << food << " size=" << occupancy.size() << " frontier=" << frontier.size() << " total_explored=" << explored_count << " total_crawled=" << crawled_count << " frontier_best_cost=" << frontier.front().cost() << " frontier_worst_cost=" << frontier.back().cost() << std::endl;
#endif

    if (initial_food >= environment->getCrawlCost()) {
      initial_food -= environment->getCrawlCost();
    } else {
      const float k = environment->getCrawlCost() / occupancy.size();
      for (const auto& s : occupancy) {
        environment->eatFood(s, k);
      }
    }

    float food_diff = 0.0f;

    for (const auto& s : occupancy)
      food_diff += environment->getFood(s);

    occupancy.erase(std::remove_if(occupancy.begin(), occupancy.end(), [&](const Solution& s) {
      return environment->getFood(s) < (environment->getFood(frontier.back()) - environment->getCrawlCost());
    }), occupancy.end());

    for (const auto& s : occupancy)
      food_diff -= environment->getFood(s);

    food -= food_diff;

    occupancy.push_back(frontier.front());
    crawled_count++;

    food -= environment->getCrawlCost();
    food += environment->getFood(frontier.front());

#ifdef LOG
    std::cerr << "plasmodium=" << id << " state=crawled food=" << food << " size=" << occupancy.size() << " frontier=" << frontier.size() << " total_explored=" << explored_count << " total_crawled=" << crawled_count << std::endl;
#endif
  }
  else {
#ifdef LOG
    std::cerr << "plasmodium=" << id << " state=not_crawled food=" << food << " size=" << occupancy.size() << " frontier=" << frontier.size() << " total_explored=" << explored_count << " total_crawled=" << crawled_count << std::endl;
#endif
  }
}

}
}
