#ifndef PUT_PHYSARUM_QAP_ENVIRONMENT_HPP_
#define PUT_PHYSARUM_QAP_ENVIRONMENT_HPP_

#include "./solution.hpp"
#include <map>

namespace PUT {
namespace Physarum {

class Environment {
  public:
    Environment(const Problem &p, float initial_food, float explore_cost, float crawl_cost);

    void calibrate(unsigned long long c);
    float getInitialFood(const Solution& solution);
    void eatFood(const Solution& solution, float f);
    float getFood(const Solution& solution);
    float getExploreCost() { return explore_cost; }
    float getCrawlCost() { return crawl_cost; }
    Problem& getProblem() { return problem; }

  private:
    Problem problem;
    float initial_food;
    float explore_cost;
    float crawl_cost;

    float best_cost;

    std::map<Solution, float, Solution::Comparator> food_eaten;
};

}
}

#endif
