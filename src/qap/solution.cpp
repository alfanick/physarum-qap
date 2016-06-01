#include "./solution.hpp"

#include <random>

namespace PUT {
namespace Physarum {

Solution::Solution(Problem* p) : problem(p) {
  assignment.resize(problem->getSize());

  for (size_t i = 0; i < assignment.size(); i++)
    assignment[i] = i;

  std::mt19937 r{std::random_device{}()};
  std::shuffle(assignment.begin(), assignment.end(), r);
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

  std::copy(s.assignment.begin(), s.assignment.end(), std::ostream_iterator<size_t>(os, " "));

  return os;
}


}
}