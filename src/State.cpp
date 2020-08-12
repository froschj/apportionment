/*
* State class to support apportionment program
*/

#include "State.hpp"

#include <string>

//construct a blank State
State::State() : State("", 0) {}

//construct a state with a  name and a population.
//all States start with 1 seat apportioned
State::State(std::string stateName, unsigned long long statePopulation) {
  this->setName(stateName);
  this->setPopulation(statePopulation);
  this->seats = 1;
}

//copy constructor for a State
State::State (const State &rhs) {
  this->name = rhs.name;
  this->population = rhs.population;
  this->seats = rhs.seats;
}

//assignment operator
State operator= (const State &rhs) {
  this->name = rhs.name;
  this->population = rhs.population;
  this->seats = rhs.seats;
}

//no destructor required
State::~State() {}

//set the name of the state
void State::setName(stateName) {
  this->name = stateName;
}

//set the population of a State
void State::setPopulation(statePopulation) {
  this->population = statePopulation;
}

//increment the number of seats apportioned to a State
void State::addSeat() {
  ++(this->seats);
  this->setPriority();
}

//return the name of the state
std::string getName() {
  return this->name;
}

//return a states population
unsigned long State::getPopulation() {
  return this->population;
}

//return a states current number of seats
unsigned State::getSeats() {
  return this->seats;
}

//compare functor for putting a container of States in Alpha order by name
StateAlpha::StateAlpha(const bool& revparam=false) {
  reverse=revparam;
}

bool StateAlpha::operator() (const State &lhs, const State &rhs) const
{
  if (reverse) return (lhs.getName().compare(rhs.getName()) < 0);
  else return (rhs.getName().compare(lhs.getName()) < 0);
}
