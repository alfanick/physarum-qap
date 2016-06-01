#include "./environment.hpp"

namespace PUT {
namespace Physarum {

Environment::Environment(const Problem &p, float ifd, float ec, float cc) : problem(p), initial_food(ifd), explore_cost(ec), crawl_cost(cc) {

}

void Environment::calibrate(unsigned long long c) {
  best_cost = c;
}

float Environment::getInitialFood(const Solution& solution) {
  return initial_food + getFood(solution);
}

float Environment::getFood(const Solution& solution) {
  return best_cost / solution.cost();
}

}
}
