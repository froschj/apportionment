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

double State::getPriority() {
  return this->getPriority;
}

unsigned State::getSeats() {
  return this->seats;
}

StatePriority::StatePriority(const bool& revparam=false) {
  reverse=revparam;
}

bool StatePriority::operator() (const State *lhs, const State *rhs) const
{
  if (reverse) return (lhs->getPriority() > rhs->getPriority());
  else return (lhs->getPriority() < rhs->getPriority());
}

StateAlpha::StateAlpha(const bool& revparam=false) {
  reverse=revparam;
}

bool StateAlpha::operator() (const State *lhs, const State *rhs) const
{
  if (reverse) return (lhs->getPriority() > rhs->getPriority());
  else return (lhs->getPriority() < rhs->getPriority());
}
