/*
* State class to support apportionment program
*/

#include "State.hpp"

#include <string>

State::State() : State("", 0) {}

State::State(std::string stateName, unsigned long long statePopulation) {
  this->setName(stateName);
  this->setPopulation(statePopulation);
  this->seats = 1;
}

State::State (const State &rhs) {
  this->name = rhs.name;
  this->population = rhs.population;
  this->seats = rhs.seats;
}

State::~State() {}

void State::setName(stateName) {
  this->name = stateName;
}

void State::setPopulation(statePopulation) {
  this->population = statePopulation;
}

void State::addSeat() {
  ++(this->seats);
  this->setPriority();
}

std::string getName() {
  return this->name;
}

unsigned long long State::getPopulation() {
  return this->population;
}

unsigned State::getSeats() {
  return this->seats;
}

StateAlpha::StateAlpha(const bool& revparam=false) {
  reverse=revparam;
}

bool StateAlpha::operator() (const State &lhs, const State &rhs) const
{
  if (reverse) return (lhs.getName().compare(rhs.getName()) < 0);
  else return (rhs.getName().compare(lhs.getName()) < 0);
}
