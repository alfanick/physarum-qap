#include "./plasmodium.hpp"

namespace PUT {
namespace Physarum {

Plasmodium::Plasmodium(Environment* e, Solution position, float i) : initial_food(i), environment(e) {
  id = next_id();
  size = position.assignment.size();
  explored_count = 0;
  crawled_count = 0;
  occupancy.push_back(position);
  food = initial_food + e->getFood(position);
  alive = true;

  std::cerr << id << " " << e->getFood(position) << " " << position.cost() << std::endl;
}

void Plasmodium::explore() {
  float explore_cost = environment->getExploreCost();
  frontier.clear();

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

      frontier.push_back(solution);
      explored_count++;
    }

  }
}

void Plasmodium::crawl() {
  if (frontier.empty()) {
    alive = false;
    std::cerr << "dead " << id << std::endl;
    return;
  }

  std::sort(frontier.begin(), frontier.end(), [&](const Solution& a,  const Solution& b) {
    return environment->getFood(a) > environment->getFood(b);
  });

  if (environment->getFood(frontier.front()) > (environment->getCrawlCost() + environment->getExploreCost())) {
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

    // std::cerr << '#' << id << " pre " << occupancy.size();
    occupancy.erase(std::remove_if(occupancy.begin(), occupancy.end(), [&](const Solution& s) {
      return environment->getFood(s) < (environment->getFood(frontier.back()) - environment->getCrawlCost());
    }), occupancy.end());
    // std::cerr << " post " << occupancy.size() << std::endl;

    for (const auto& s : occupancy)
      food_diff -= environment->getFood(s);

    food -= food_diff;

    occupancy.push_back(frontier.front());
    crawled_count++;

    // std::cerr << '#' << id << ' ' << occupancy.size() << ' ' << food << std::endl;
    food -= environment->getCrawlCost();
    food += environment->getFood(frontier.front());
  }
}

}
}
