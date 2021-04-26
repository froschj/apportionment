/*
* State class to support apportionment program
*/

#ifndef STATE_HPP
#define STATE_HPP

#include <string>

//class to store data by state
class State {
public:
  //construct a blank State with 1 apportioned seat
  State();
  //construct a state with a  name and a population.
  //all States start with 1 seat apportioned
  State(const std::string stateName, const unsigned long statePopulation);
  //copy constructor for a State
  State(const State &rhs);
  //assignment operator
  State& operator= (const State &rhs);

  void setName(const std::string stateName);
  //set the population of a State
  void setPopulation(const unsigned long statePopulation);
  //increment the number of seats apportioned to a State
  void addSeat();

  //return the name of the state
  std::string getName() const;
  //return a states population
  unsigned long getPopulation() const;
  //return a states current number of seats
  unsigned getSeats() const;

  ~State();
protected:
  std::string name;
  unsigned long population;
  unsigned seats;

};

//functor for ordering states by name
class StateAlpha {
  bool reverse;
public:
  StateAlpha(const bool& revparam=false);
  bool operator() (
    const State &lhs, const State &rhs
  ) const;
};

#endif
