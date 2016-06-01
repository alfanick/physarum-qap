#ifndef PUT_PHYSARUM_QAP_SOLUTION_HPP_
#define PUT_PHYSARUM_QAP_SOLUTION_HPP_

#include "./problem.hpp"

#include <iostream>

namespace PUT {
namespace Physarum {

class Problem;
class Solution {
  public:
    class Comparator {
      public:
        bool operator()(const Solution& a, const Solution& b) const {
          return a.assignment < b.assignment;
        }
    };

    Solution(Problem* problem);
    Solution(Problem* problem, const std::vector<int> &assignment);

    unsigned long long cost() const;

    std::vector<size_t> assignment;

    bool operator<(const Solution& other) const;

  private:
    Problem* problem;
};

std::ostream &operator<<(std::ostream &os, Solution const &s);

}
}

#endif
