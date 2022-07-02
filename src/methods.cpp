#include "State.hpp"
#include "methods.hpp"
#include "Apportionment.hpp"
#include <string>
#include <cmath>

/* Adams method: priority = population / curSeats
 * (floor)
 * considered 1830, not used
 * (most favorable to small states)
 */
double adams(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;

  //will always divide by 'a', fmin() used for consistency
  p = state.getPopulation() / static_cast<double>(fmin(a, b));
  return p;
}

/* Dean method: priority = population / harmonicMean(curSeats, curSeats + 1)
 * 
 * considered 1830, not used
 */
double dean(const State &state) {
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

/* Huntington-Hill method:
 *
 * priority = population / geometricMean(curSeats, curSeats + 1)
 * used 1940 on
 */
double huntingtonHill(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double GM;

  GM = sqrt(a * b); //geometricMean

  p = state.getPopulation() / GM;
  return p;
}

/* Webster method:
 *
 * priority = population / arithmeticMean(curSeats, curSeats + 1)
 * used 1840, 1910, 1930
 */
double webster(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;
  double AM;

  AM = (a + b) / 2.0; //arithmeticMean

  p = state.getPopulation() / AM;
  return p;
}

/* Jefferson method: priority = population / (curSeats + 1)
 * (ceiling)
 * used 1790-1830
 * (most favorable to large states)
 */
double jefferson(const State &state) {
  double p;
  unsigned a = state.getSeats();
  unsigned b = a + 1;

  //will always divide by 'b', fmin() used for consistency
  p = state.getPopulation() / static_cast<double>(fmax(a, b));
  return p;
}
