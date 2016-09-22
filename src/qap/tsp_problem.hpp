#ifndef PUT_PHYSARUM_QAP_TSP_PROBLEM_HPP_
#define PUT_PHYSARUM_QAP_TSP_PROBLEM_HPP_

#include "problem.hpp"

namespace PUT {
namespace Physarum {

class TspProblem : public Problem {
  public:
    TspProblem();
    TspProblem(std::string path);

    virtual unsigned long long cost(Solution solution);
};

}
}

#endif
