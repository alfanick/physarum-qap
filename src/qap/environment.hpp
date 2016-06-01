#ifndef PUT_PHYSARUM_QAP_ENVIRONMENT_HPP_
#define PUT_PHYSARUM_QAP_ENVIRONMENT_HPP_

#include "./solution.hpp"

namespace PUT {
namespace Physarum {

class Environment {
  public:
    Environment(const Problem &p, float initial_food, float explore_cost, float crawl_cost);

    void calibrate(unsigned long long c);
    float getInitialFood(const Solution& solution);
    float getFood(const Solution& solution);
    Problem& getProblem() { return problem; }

  private:
    Problem problem;
    float initial_food;
    float explore_cost;
    float crawl_cost;

    float best_cost;
};

}
}

#endif
