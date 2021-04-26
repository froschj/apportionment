#include "State.hpp"
#include "Apportionment.hpp"

#include <queue>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <tuple>

//create a new apportionment object
Apportionment::Apportionment() {
  (this->states).clear();
  this->seatsApportioned = 0;
}

//apportion <seats> seats amon the states stored in the apportionment
void Apportionment::apportion(unsigned seats) {
  for (int i = 0; i < seats; ++i) {
    this->addSeat();
  }
}

//apportion a seat to the highest priority state
void Apportionment::addSeat() {
  //remove the highest priority state from the heap
  std::pop_heap(states.begin(), states.end(), StatePriority());

  //add a seat and adjust priority
  std::get<0>(states.back()).addSeat();
  std::get<1>(states.back()) = priority(std::get<0>(states.back()));
  ++seatsApportioned;

  //re-insert adjusted state into the heap
  std::push_heap(states.begin(), states.end(), StatePriority());
}

//return the number of seats apportioned
unsigned Apportionment::getSeatsApportioned() {
  return seatsApportioned;
}

//add a State to the apportionment
void Apportionment::addState(State state) {
  //add a new State, priotity tuple to the vector
  states.emplace_back(std::make_tuple(state, this->priority(state)));
  //account for any seats the new state may have
  seatsApportioned += std::get<0>(states.back()).getSeats();
  //add the new State to the heap
  std::push_heap(states.begin(), states.end(), StatePriority());
}

//return a vector of states representing the current state of the
//Apportionment
std::vector<State> Apportionment::getStates() const {
  std::vector<State> temp;
  //iterate through internal (heap) vector and copy States into new vector
  for (auto it = states.cbegin(); it != states.cend(); ++it) {
    temp.emplace_back(std::get<0>(*it));
  }
  return temp;
}

//return the name of the highest-priority state
std::string Apportionment::topStateName() const {
  return std::get<0>(states.front()).getName();
}

//return the current seats of the highest priority state
unsigned Apportionment::topStateSeats() const {
  return std::get<0>(states.front()).getSeats();
}

//return the current highest priority number
double Apportionment::topStatePriority() const {
  return std::get<1>(states.front());
}

//return the number of states in the apportionment
unsigned Apportionment::getNumStates() const {
  return states.size();
}

//no custom destructor needed
Apportionment::~Apportionment() {}

//comparison functor to implement priority queue behavior in our tuple vector
StatePriority::StatePriority(const bool& revparam) {
  reverse=revparam;
}

bool StatePriority::operator() (
  const std::tuple<State, double> lhs, const std::tuple<State, double> rhs
) const
{
  if (reverse) return (std::get<1>(lhs) > std::get<1>(rhs));
  else return (std::get<1>(lhs) < std::get<1>(rhs));
}
