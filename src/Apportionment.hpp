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
#include <functional>

class Apportionment {
public:
  //create a new apportionment object
  //Apportionment();
  //create an apportionment object with a selected method
  Apportionment(std::function<double(const State&)>);
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
  //set the apportionment method to use
  //void setMethod(std::function<double(const State&)> newMethod);
  //destructor
  ~Apportionment();
private:
  //store each state with a corresponding priority value
  std::vector<std::tuple<State, double>> states;
  unsigned seatsApportioned;
  //store the function we will use to determine priority
  std::function<double(const State&)> priority;
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
