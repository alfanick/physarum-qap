#include "./solution.hpp"

#include <random>

namespace PUT {
namespace Physarum {

Solution::Solution(Problem* p) : problem(p) {
  assignment.resize(problem->getSize());

  for (size_t i = 0; i < assignment.size(); i++)
    assignment[i] = i;

  std::shuffle(assignment.begin(), assignment.end(), problem->generator);
}

Solution::Solution(Problem* p, const std::vector<int> &assignment) : problem(p) {
  std::copy(assignment.begin(), assignment.end(), this->assignment.begin());
}

unsigned long long Solution::cost() const {
  return problem->cost(*this);
}

bool Solution::operator<(const Solution& other) const {
  return other.cost() < cost();
}

std::ostream &operator<<(std::ostream &os, Solution const &s) {
  os << s.assignment.size() << ' ' << s.cost() << std::endl;

  for (size_t a : s.assignment) {
    os << a+1 << ' ';
  }

  return os;
}


}
}
