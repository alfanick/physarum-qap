#ifndef PUT_PHYSARUM_QAP_PLASMODIUM_HPP_
#define PUT_PHYSARUM_QAP_PLASMODIUM_HPP_

#include <atomic>
#include "./problem.hpp"
#include "./environment.hpp"

namespace PUT {
namespace Physarum {

class Plasmodium {
  public:
    Plasmodium(Environment* e, Solution position, float food);

    void explore();
    void crawl();

    float getFood() { return food; }
    size_t getId() { return id; }
    std::vector<Solution> getPositions() { return occupancy; }
    size_t getExploredCount() { return explored_count; }
    size_t getCrawledCount() { return crawled_count; }
    bool isAlive() { return alive; }

  private:
    std::vector<Solution> occupancy;
    std::vector<Solution> frontier;
    float food;
    float initial_food;
    Environment* environment;
    bool alive;
    size_t id;
    size_t size;
    size_t explored_count;
    size_t crawled_count;

    static size_t next_id() {
      static std::atomic_size_t id_generator(0);
      return id_generator++;
    }

    friend class Experiment;
};

}
}

#endif
