#include "tsp_problem.hpp"

#include <fstream>

namespace PUT {
namespace Physarum {

TspProblem::TspProblem() {
  path = "/dev/null";
  size = 0;
  generator.seed(rand());
}

TspProblem::TspProblem(std::string path) : TspProblem() {
  std::ifstream definition(path);

  this->path = path;

  definition >> size;

  distance.resize(size);

  for (size_t i = 0; i < size; i++) {
    distance[i].resize(size);
  }

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      definition >> distance[i][j];
    }
  }
}

unsigned long long TspProblem::cost(Solution solution) {
  unsigned long long total = 0;

  for (size_t i = 0; i < size-1; i++) {
    total += distance[solution.assignment[i]][solution.assignment[i+1]];
  }

  return total;
}

}
}
