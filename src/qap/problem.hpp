#ifndef PUT_PHYSARUM_QAP_PROBLEM_HPP_
#define PUT_PHYSARUM_QAP_PROBLEM_HPP_

#include <vector>
#include <string>
#include <random>

#include "./solution.hpp"

namespace PUT {
namespace Physarum {

class Solution;
class Problem {
  public:
    Problem();
    Problem(std::string path);

    virtual unsigned long long cost(Solution solution);

    size_t getSize() { return size; }

    std::mt19937 generator{std::random_device{}()};
  protected:
    size_t size;

    std::vector<std::vector<unsigned int>> flow;
    std::vector<std::vector<unsigned int>> distance;

    std::string path;
};

}
}

#endif
