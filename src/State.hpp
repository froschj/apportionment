/*
* State class to support apportionment program
*/

#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class State {
public:
  State();
  State(const std::string stateName, const unsigned long statePopulation);
  State(const State &rhs);

  void setName(const std::string stateName);
  void setPopulation(const unsigned long statePopulation);
  void addSeat();

  std::string getName();
  unsigned long getPopulation();
  unsigned getSeats();

  ~State();
protected:
  std::string name;
  unsigned long population;
  unsigned seats;

};

class StateAlpha {
  bool reverse;
public:
  StateAlpha(const bool& revparam=false);
  bool operator() (
    const State &lhs, const State &rhs
  ) const;
};

#endif
