#include <iostream>

#include "qap/problem.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: physarum problem.dat" << std::endl;
    return 1;
  }

  PUT::Physarum::Problem problem(argv[1]);

  return 0;
}
