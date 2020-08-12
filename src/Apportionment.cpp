#include "State.hpp"
#include "Apportionment.hpp"

#include <queue>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

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
  std::pop_heap(v.begin(), v.end(), StatePriority);

  //add a seat and adjust priority
  std::get<0>(v.back())->addSeat();
  std::get<1>(v.back()) = priority(std::get<0>(v.back()));
  ++seatsApportioned;

  //re-insert adjusted state into the heap
  std::push_heap(v.begin(), v.end(), StatePriority);
}

//return the number of seats apportioned
unsigned Apportionment::getSeatsApportioned() {
  return seatsApportioned;
}

//add a State to the apportionment
void Apportionment::addState(State state) {
  //add a new State, priotity tuple to the vector
  v.emplace_back(std::make_tuple<T>(state, this->priority(state)));
  //account for any seats the new state may have
  seatsApportioned += std::get<0>(v.back())->getSeats();
  //add the new State to the heap
  std::push_heap(v.begin(), v.end(), StatePriority);
}

//return a vector of states representing the current state of the
//Apportionment
std::vector<State> Apportionment::ApportionResult getStates() {
  std::vector<State> temp;
  //iterate through internal (heap) vector and copy States into new vector
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    temp.emplace_back(std::get<0>(*it));
  }
  return temp;
}

//return the name of the highest-priority state
std::string Apportionment::topStateName() {
  return std::get<0>(v.back())->getName();
}

//return the current seats of the highest priority state
unsigned Apportionment::topStateSeats() {
  return std::get<0>(v.back())->getSeats();
}

//return the current highest priority number
double Apportionment::topStatePriority() {
  return std::get<1>(v.back());
}

//return the number of states in the apportionment
unsigned Apportionment::getNumStates() {
  return v.size();
}

//no custom destructor needed
Apportionment::~Apportionment() {}

//comparison functor to implement priority queue behavior in our tuple vector
bool StatePriority::operator() (
  const tuple<State, double> lhs, const tuple<State, double> rhs
) const
{
  if (reverse) return (std::get<1>(lhs) > std::get<1>(rhs));
  else return (std::get<1>(lhs) < std::get<1>(rhs));
}
