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

    std::vector<Solution> frontier();

    float getFood() { return food; }
    size_t getId() { return id; }
    std::vector<Solution> getPositions() { return occupancy; }

  private:
    std::vector<Solution> occupancy;
    float food;
    Environment* environment;
    size_t id;

    static size_t next_id() {
      static std::atomic_size_t id_generator(0);
      return id_generator++;
    }
};

}
}

#endif
