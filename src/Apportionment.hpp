/*
 * Abstract class interface for appoortiong seats using priority methods
 */

#ifndef APPORTIONMENT_HPP
#define APPORTIONMENT_HPP

#include "State.hpp"

#include <queue>
#include <vector>
#include <memory>
#include <string>
#include <tuple>

class Apportionment {
public:
  //create a new apportionment object
  Apportionment();
  //apportion <seats> seats amon the states stored in the apportionment
  void apportion(unsigned seats);
  //apportion a seat to the highest priority state
  void addSeat();
  //return the number of seats apportioned
  unsigned getSeatsApportioned();
  //add a State to the apportionment
  void addState(State state);
  //return a vector of states representing the current state of the
  //Apportionment
  std::vector<State> getStates() const;
  //return the name of the highest-priority state
  std::string topStateName() const;
  //return the current seats of the highest priority state
  unsigned topStateSeats() const;
  //return the current highest priority number
  double topStatePriority() const;
  //return the number of states in the apportionment
  unsigned getNumStates() const;
  //needed for polymorphism
  virtual ~Apportionment();
private:
  //store each state with a corresponding priority value
  std::vector<std::tuple<State, double>> states;
  unsigned seatsApportioned;
  //override in derived classes to implement different apportiomment methods
  virtual double priority(const State &state) = 0;
};

//comparison functor to implement priority queue behavior in our tuple vector
class StatePriority {
  bool reverse;
public:
  StatePriority(const bool& revparam=false);
  bool operator() (
    const std::tuple<State, double> lhs, const std::tuple<State, double> rhs
  ) const;
};

#endif
