#ifndef APPORTIONMENT_HPP
#define APPORTIONMENT_HPP

#include "State.hpp"

#include <queue>
#include <vector>
#include <memory>
#include <string>

struct ApportionResult {
  std::string stateName;
  unsigned seats;
  unsigned long long population;
  ApportionResult(std::string n, unsigned s, unsigned long long p) :
    stateName(std::move(n)), seats(s), population(p) {}
};

class Apportionment {
public:
  Apportionment();
  void apportion(unsigned seats);
  void addSeat();
  unsigned getSeatsApportioned();
  void addState(std::string stateName, unsigned long long statePop);
  std::vector<struct ApportionResult> getStates();
  std::string topStateName();
  unsigned topStateSeats();
  unsigned long long topStatePriority();
  unsigned getNumStates();
  ~Apportionment();
private:
  std::vector<std::unique_ptr<State>> states;
  unsigned seatsApportioned;
};



#endif
