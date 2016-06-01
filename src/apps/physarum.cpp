#include <iostream>

#include "qap/experiment.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: physarum problem.dat" << std::endl;
    return 1;
  }

  std::srand(time(0));

  PUT::Physarum::Problem problem(argv[1]);
  PUT::Physarum::Environment environment(problem, 1.0, 0.01, 0.01);
  PUT::Physarum::Experiment experiment(environment, 500, 20);

  experiment.run(1);

  std::cout << experiment.getSolution() << std::endl;

  return 0;
}
