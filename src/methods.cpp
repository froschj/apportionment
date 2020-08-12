#include "State.hpp"
#include "methods.hpp"
#include "Apportionment.hpp"
#include <string>
#include <cmath>

Adams::Adams() {}
Adams::~Adams() {}
double Adams::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;

  //will always divide by 'a', fmin() used for consistency
  p = state.getPopulation() / static_cast<double>fmin(a, b);
  return p;
}

Dean::Dean() {}
Dean::~Dean() {}
Dean::priority(const State &state) {
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

HuntingtonHill::HuntingtonHill() {}
HuntingtonHill::~HuntingtonHill() {}
HuntingtonHill::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double GM;

  GM = sqrt(a * b); //geometricMean

  p = state.getPopulation() / GM;
  return p;
}

Webster::Webster() {}
Webster::~Webster() {}
Webster::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double AM;

  AM = (a + b) / 2.0; //arithmeticMean

  p = state.getPopulation() / AM;
  return = p;
}

Jefferson::Jefferson() {}
Jefferson::~Jefferson() {}
Jefferson::priority(const State &state) {
  double p;
  unsigned a = seats;
  unsigned b = seats + 1;

  //will always divide by 'b', fmin() used for consistency
  p = state.getPopulation() / static_cast<double>fmax(a, b);
  return p;
}
