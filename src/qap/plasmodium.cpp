#include "./plasmodium.hpp"

namespace PUT {
namespace Physarum {

Plasmodium::Plasmodium(Environment* e, Solution position, float f) : food(f), environment(e) {
  id = next_id();
  size = position.assignment.size();
  explored_count = 0;
  crawled_count = 0;
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

    int i = 1;
    for (auto solution : occupancy) {
      // if (rand() > (float(i) / float(occupancy.size())) * RAND_MAX)
      //   continue;

      environment->eatFood(solution, explore_cost);

      std::swap(solution.assignment[a], solution.assignment[b]);

      frontier.push_back(solution);
      explored_count++;

      food -= explore_cost;

      i++;
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
    crawled_count++;

    food -= environment->getCrawlCost();
    food += environment->getFood(frontier[0]);
  }
}

}
}
