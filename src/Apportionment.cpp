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
  v.back()->addSeat();
  ++seatsApportioned;
  std::push_heap(v.begin(), v.end(), StatePriority);
}

unsigned getSeatsApportioned() {
  return seatsApportioned;
}

void addState(std::string stateName, unsigned long long statePop) {
  v.emplace_back(std::make_unique<T>(stateName, statePop));
  seatsApportioned += (v.back())->getSeats();
  std::push_heap(v.begin(), v.end(), StatePriority);
}

struct ApportionResult getStates() {
  std::vector<struct ApportionResult> temp;
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    temp.emplace_back(
      (**it)->getName(),
      (**it)->getSeats(),
      (**it)->getPopulation()
    );
  }
  return temp;
}

std::string topStateName() {
  return (v.back())->getName();
}

unsigned topStateSeats() {
  return (v.back())->getSeats();
}

unsigned long long topStatePriority() {
  return (v.back())->getPriority();
}

unsigned getNumStates() {
  return v.size();
}
~Apportionment();
