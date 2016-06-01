#include "./plasmodium.hpp"

namespace PUT {
namespace Physarum {

Plasmodium::Plasmodium(Environment* e, Solution position, float f) : food(f), environment(e) {
  id = next_id();
  size = position.assignment.size();
  occupancy.push_back(position);

  std::cerr << id << " " << f << std::endl;
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
      environment->eatFood(solution, explore_cost / occupancy.size());

      std::swap(solution.assignment[a], solution.assignment[b]);

      frontier.push_back(solution);

      food -= explore_cost;
    }

  }
}

void Plasmodium::crawl() {
  std::sort(frontier.begin(), frontier.end(), [&](const Solution& a,  const Solution& b) {
    return environment->getFood(a) > environment->getFood(b);
  });

  if (environment->getFood(frontier[0]) > (food - environment->getCrawlCost())) {
    occupancy.erase(std::remove_if(occupancy.begin(), occupancy.end(), [&](const Solution& s) {
      return environment->getFood(s) < (environment->getFood(frontier.back()) - environment->getCrawlCost());
    }), occupancy.end());

    occupancy.push_back(frontier[0]);

    food -= environment->getCrawlCost();
    food += environment->getFood(frontier[0]);
  }
}

}
}
