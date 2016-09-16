#include "./problem.hpp"

#include <fstream>

namespace PUT {
namespace Physarum {

Problem::Problem() {
  path = "/dev/null";
  size = 0;
  generator.seed(rand());
}

Problem::Problem(std::string path) : Problem() {
  std::ifstream definition(path);

  this->path = path;

  definition >> size;

  flow.resize(size);
  distance.resize(size);

  for (size_t i = 0; i < size; i++) {
    flow[i].resize(size);
    distance[i].resize(size);
  }

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      definition >> distance[i][j];
    }
  }

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      definition >> flow[i][j];
    }
  }
}

unsigned long long Problem::cost(Solution solution) {
  unsigned long long total = 0;

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      total += flow[solution.assignment[i]][solution.assignment[j]] * distance[i][j];
    }
  }

  return total;
}

unsigned long long Problem::cost(Solution solution, unsigned long long previous_cost, size_t a, size_t b) {
  return 0;
}

}
}
