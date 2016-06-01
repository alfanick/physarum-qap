#ifndef PUT_PHYSARUM_QAP_PROBLEM_HPP_
#define PUT_PHYSARUM_QAP_PROBLEM_HPP_

#include <vector>
#include <string>

#include "./solution.hpp"

namespace PUT {
namespace Physarum {

class Solution;
class Problem {
  public:
    Problem();
    Problem(std::string path);

    unsigned long long cost(Solution solution);
    unsigned long long cost(Solution solution, unsigned long long previous_cost, size_t a, size_t b);

    size_t getSize() { return size; }

  private:
    size_t size;

    std::vector<std::vector<unsigned int>> flow;
    std::vector<std::vector<unsigned int>> distance;

    std::string path;
};

}
}

#endif
