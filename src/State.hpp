/*
* State class to support apportionment program
*/

#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class State {
public:
  State();
  State(std::string stateName, unsigned long long statePopulation);

  void setName(std::string stateName);
  void setPopulation(unsigned long long statePopulation);
  void addSeat();

  std::string getName();
  unsigned long long getPopulation();
  double getPriority();
  unsigned getSeats();

  virtual ~State();
protected:
  std::string name;
  unsigned long long population;
  unsigned seats;
  double priority;
  virtual void setPriority() = 0;
};

class StatePriority {
  bool reverse;
public:
  StatePriority(const bool& revparam=false);
  bool operator() (const State *lhs, const State *rhs) const;
};

#endif
