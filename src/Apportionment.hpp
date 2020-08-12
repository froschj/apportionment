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
  Apportionment();
  void apportion(unsigned seats);
  void addSeat();
  unsigned getSeatsApportioned();
  void addState(State);
  std::vector<State> getStates() const;
  std::string topStateName() const;
  unsigned topStateSeats() const;
  double topStatePriority() const;
  unsigned getNumStates() const;
  virtual ~Apportionment();
private:
  std::vector<tuple<State, double>> states;
  unsigned seatsApportioned;
  virtual double priority(const State &state) = 0;
};

class StatePriority {
  bool reverse;
public:
  StatePriority(const bool& revparam=false);
  bool operator() (
    const tuple<State, double> lhs, const tuple<State, double> rhs
  ) const;
};

#endif
