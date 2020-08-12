#include "State.hpp"
#include "methods.hpp"
#include <string>
#include <cmath>

Adams::Adams() : Adams("", 0) {}

Adams::Adams(std::string stateName, unsigned long long statePopulation) :
  State(stateName, statePopulation){
  this->setPriority;
}

Adams::~Adams() {}

Adams::setPriority() {
  double p;
  unsigned long long a = seats;
  unsigned long long b = seats + 1;

  p = population/static_cast<double>fmin(a, b);
  this->priority = p;
}

Dean::Dean() : Dean("", 0) {}

Dean::Dean(std::string stateName, unsigned long long statePopulation) :
  State(stateName, statePopulation){
  this->setPriority;
}

Dean::~Dean() {}

Dean::setPriority() {
  double p;
  unsigned long long a = seats;
  unsigned long long b = seats + 1;
  double AM, GM, HM;

  AM = (a + b) / 2;
  GM = sqrt(a * b);
  HM = (GM * GM) / AM;

  p = population/HM;
  this->priority = p;
}

HuntingtonHill::HuntingtonHill() : HuntingtonHill("", 0) {}

HuntingtonHill::HuntingtonHill(std::string stateName,
    unsigned long long statePopulation) :
  State(stateName, statePopulation){
  this->setPriority;
}

HuntingtonHill::~HuntingtonHill() {}

HuntingtonHill::setPriority() {
  double p;
  unsigned long long a = seats;
  unsigned long long b = seats + 1;
  double GM;

  GM = sqrt(a * b);

  p = population/GM;
  this->priority = p;
}

Webster::Webster() : Webster("", 0) {}

Webster::Webster(std::string stateName, unsigned long long statePopulation) :
  State(stateName, statePopulation){
  this->setPriority;
}

Webster::~Webster() {}

Webster::setPriority() {
  double p;
  unsigned long long a = seats;
  unsigned long long b = seats + 1;
  double AM;

  AM = (a + b) / 2;

  p = population/AM;
  this->priority = p;
}

Jefferson::Jefferson() : Jefferson("", 0) {}

Jefferson::Jefferson(std::string stateName, unsigned long long statePopulation) :
  State(stateName, statePopulation){
  this->setPriority;
}

Jefferson::~Jefferson() {}

Jefferson::setPriority() {
  double p;
  unsigned long long a = seats;
  unsigned long long b = seats + 1;

  p = population/static_cast<double>fmax(a, b);
  this->priority = p;
}
