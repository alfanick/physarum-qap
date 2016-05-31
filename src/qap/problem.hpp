#ifndef PUT_PHYSARUM_QAP_PROBLEM_HPP_
#define PUT_PHYSARUM_QAP_PROBLEM_HPP_

#include <vector>
#include <string>

namespace PUT {
namespace Physarum {

class Problem {
  public:
    Problem();
    Problem(std::string path);

    unsigned long long cost(const std::vector<int> &solution);
    unsigned long long cost(const std::vector<int> &solution, unsigned long long previous_cost, size_t a, size_t b);

  private:
    std::string path;
    size_t size;

    std::vector<std::vector<unsigned int>> flow;
    std::vector<std::vector<unsigned int>> distance;
};

}
}

#endif
