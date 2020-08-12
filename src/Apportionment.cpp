#include "State.hpp"
#include "Apportionment.hpp"

#include <queue>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

Apportionment::Apportionment() {
  (this->states).clear();
  this->seatsApportioned = 0;
}

void Apportionment::apportion(unsigned seats) {
  for (int i = 0; i < seats; ++i) {
    this->addSeat();
  }
}

void Apportionment::addSeat() {
  std::pop_heap(v.begin(), v.end(), StatePriority);
  std::get<0>(v.back())->addSeat();
  std::get<1>(v.back()) = priority(std::get<0>(v.back()));
  ++seatsApportioned;
  std::push_heap(v.begin(), v.end(), StatePriority);
}

unsigned Apportionment::getSeatsApportioned() {
  return seatsApportioned;
}

void Apportionment::addState(State state) {
  v.emplace_back(std::make_tuple<T>(state, this->priority(state)));
  seatsApportioned += std::get<0>(v.back())->getSeats();
  std::push_heap(v.begin(), v.end(), StatePriority);
}

struct Apportionment::ApportionResult getStates() {
  std::vector<State> temp;
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    temp.emplace_back(std::get<0>(*it));
  }
  return temp;
}

std::string Apportionment::topStateName() {
  return std::get<0>(v.back())->getName();
}

unsigned Apportionment::topStateSeats() {
  return std::get<0>(v.back())->getSeats();
}

double Apportionment::topStatePriority() {
  return std::get<1>(v.back());
}

unsigned Apportionment::getNumStates() {
  return v.size();
}

Apportionment::~Apportionment() {}

bool StatePriority::operator() (
  const tuple<State, double> lhs, const tuple<State, double> rhs
) const
{
  if (reverse) return (std::get<1>(lhs) > std::get<1>(rhs));
  else return (std::get<1>(lhs) < std::get<1>(rhs));
}
