#include "./plasmodium.hpp"

namespace PUT {
namespace Physarum {

Plasmodium::Plasmodium(Environment* e, Solution position, float f) : food(f), environment(e) {
  id = next_id();
  occupancy.push_back(position);

  std::cout << id << " " << f << std::endl;
}

void Plasmodium::explore() {

}

void Plasmodium::crawl() {

}

}
}
