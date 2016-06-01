#ifndef PUT_PHYSARUM_QAP_EXPERIMENT_HPP_
#define PUT_PHYSARUM_QAP_EXPERIMENT_HPP_

#include "./environment.hpp"
#include "./solution.hpp"
#include "./plasmodium.hpp"
#include "./environment.hpp"

namespace PUT {
namespace Physarum {

class Experiment {
  public:
    Experiment(const Environment &environment, size_t sample_size, size_t initial_population_size);

    void run() { run(10); }
    void run(unsigned int max_time);
    Solution getSolution();

    size_t getSampleSize() { return sample_size; }
    size_t getInitialPopulationSize() { return initial_population_size; }

  private:
    Environment environment;
    size_t sample_size;
    size_t initial_population_size;

    std::vector<Plasmodium> population;
};

}
}

#endif
