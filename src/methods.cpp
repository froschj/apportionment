#include "State.hpp"
#include "methods.hpp"
#include "Apportionment.hpp"
#include <string>
#include <cmath>

AdamsMethod::AdamsMethod() {}
AdamsMethod::~AdamsMethod() {}
double AdamsMethod::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;

  //will always divide by 'a', fmin() used for consistency
  p = state.getPopulation() / static_cast<double>(fmin(a, b));
  return p;
}

DeanMethod::DeanMethod() {}
DeanMethod::~DeanMethod() {}
double DeanMethod::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double AM, GM, HM;

  AM = (a + b) / 2.0; // arithmeticMean
  GM = sqrt(a * b); // geometricMean
  HM = (GM * GM) / AM; //harmonicMean

  p = state.getPopulation() / HM;
  return p;
}

HuntingtonHillMethod::HuntingtonHillMethod() {}
HuntingtonHillMethod::~HuntingtonHillMethod() {}
double HuntingtonHillMethod::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double GM;

  GM = sqrt(a * b); //geometricMean

  p = state.getPopulation() / GM;
  return p;
}

WebsterMethod::WebsterMethod() {}
WebsterMethod::~WebsterMethod() {}
double WebsterMethod::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double AM;

  AM = (a + b) / 2.0; //arithmeticMean

  p = state.getPopulation() / AM;
  return p;
}

JeffersonMethod::JeffersonMethod() {}
JeffersonMethod::~JeffersonMethod() {}
double JeffersonMethod::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;

  //will always divide by 'b', fmin() used for consistency
  p = state.getPopulation() / static_cast<double>(fmax(a, b));
  return p;
}
