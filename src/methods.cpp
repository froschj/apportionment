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

  p = population / static_cast<double>fmin(a, b);
  return p;
}

Dean::Dean() {}

Dean::~Dean() {}

Dean::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double AM, GM, HM;

  AM = (a + b) / 2.0;
  GM = sqrt(a * b);
  HM = (GM * GM) / AM;

  p = population/HM;
  return p;
}

HuntingtonHill::HuntingtonHill() {}

HuntingtonHill::~HuntingtonHill() {}

HuntingtonHill::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double GM;

  GM = sqrt(a * b);

  p = population/GM;
  return p;
}

Webster::Webster() {}

Webster::~Webster() {}

Webster::priority(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned long long b = a + 1;
  double AM;

  AM = (a + b) / 2.0;

  p = population/AM;
  return = p;
}

Jefferson::Jefferson() {}

Jefferson::~Jefferson() {}

Jefferson::priority(const State &state) {
  double p;
  unsigned a = seats;
  unsigned b = seats + 1;

  p = population/static_cast<double>fmax(a, b);
  return p;
}
