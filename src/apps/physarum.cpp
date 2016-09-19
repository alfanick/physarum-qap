#include <iostream>
#include "../external/flags/Flags.hh"

#include "../qap/experiment.hpp"

int main(int argc, char** argv) {
  Flags flags;

  int seed = -1;
  unsigned int samples = 10;
  unsigned int population_size = 1;
  unsigned int time_limit = 30;

  float e_initial = 0.0;
  float e_explore = 0.001;
  float e_crawl = 0.001;
  float a = 0.1;
  float q = 10.0;
  bool should_not_merge = false;

  std::string problem_name;

  bool help = false;
  bool historical_min = false;

  flags.Var(samples, 'k', "samples", samples, "Number of initial samples", "Sampling");
  flags.Var(population_size, 'l', "population", population_size, "Number of plasmodia in colony", "Sampling");

  flags.Var(e_initial, 'i', "e_initial", e_initial, "Initial energy for each plasmodium", "Energy");
  flags.Var(e_explore, 'e', "e_explore", e_explore, "Energy required for exploration of neighbour", "Energy");
  flags.Var(e_crawl, 'c', "e_crawl", e_crawl, "Energy required for crawling to neighbour", "Energy");
  flags.Var(a, 'a', "scale", a, "Scaling factor for cost to food energy transformation", "Energy");
  flags.Var(q, 'q', "base", q, "Exponential base for cost to food energy transformation", "Energy");

  flags.Var(problem_name, 'd', "data", std::string("(unset)"), "Path to input QAP problem data", "General");
  flags.Var(time_limit, 't', "time", time_limit, "Time limit in seconds", "General");
  flags.Bool(should_not_merge, 'm', "no-merge", "Disables merging phase", "General");
  flags.Var(seed, 's', "seed", seed, "Seed for random generator, -1 for time based seed", "General");
  flags.Bool(help, 'h', "help", "Shows this help message and exit", "General");
  flags.Bool(historical_min, 'x', "historical-minimum", "Obtains solution as the best cost during whole lifetime", "General");

  if (!flags.Parse(argc, argv)) {
    flags.PrintHelp(argv[0]);
    return EXIT_FAILURE;
  } else
  if (help) {
    flags.PrintHelp(argv[0]);
    return EXIT_SUCCESS;
  } else
  if (problem_name == "(unset)") {
    std::cerr << "Input data is required!" << std::endl;

    flags.PrintHelp(argv[0]);
    return EXIT_FAILURE;
  }

  if (seed == -1) {
    std::srand(time(0));
  } else {
    std::srand(seed);
  }

  PUT::Physarum::Problem problem(problem_name);
  PUT::Physarum::Environment environment(problem, e_initial, e_explore, e_crawl, a, q);
  PUT::Physarum::Experiment experiment(environment, samples, population_size, !should_not_merge);

  experiment.run(time_limit);

  std::cout << (historical_min ? experiment.getHistoricalSolution() : experiment.getSolution()) << std::endl;

  return 0;
}

