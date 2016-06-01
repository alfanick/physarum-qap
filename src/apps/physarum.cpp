#include <iostream>

#include "qap/experiment.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: physarum problem.dat" << std::endl;
    return 1;
  }

  std::srand(time(0));

  PUT::Physarum::Problem problem(argv[1]);
  PUT::Physarum::Environment environment(problem, 1.0, 0.001, 0.03);
  PUT::Physarum::Experiment experiment(environment, problem.getSize() * problem.getSize() * problem.getSize() / 3, 20);

  experiment.run(120);

  std::cout << experiment.getSolution() << std::endl;

  return 0;
}

