#include "./environment.hpp"

namespace PUT {
namespace Physarum {

Environment::Environment(const Problem &p, float ifd, float ec, float cc) : problem(p), initial_food(ifd), explore_cost(ec), crawl_cost(cc) {

}

void Environment::calibrate(unsigned long long c) {
  best_cost = c;
}

float Environment::getInitialFood(const Solution& solution) {
  return initial_food + best_cost / solution.cost();
}

void Environment::eatFood(const Solution& solution, float f) {
  if (food_eaten.find(solution) != food_eaten.end()) {
    food_eaten[solution] += f;
  } else {
    food_eaten.emplace(solution, f);
  }
}

float Environment::getFood(const Solution& solution) {
  if (food_eaten.find(solution) != food_eaten.end()) {
    return best_cost / solution.cost() - food_eaten[solution];
  } else {
    return best_cost / solution.cost();
  }
}

}
}
