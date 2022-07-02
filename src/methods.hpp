/*
 * Priority functions to determine which state gets the "next" seat
 */

// note 1850-1900: Hamilton method - not convertible to priority. Certain sizes
// agree with Webster (1852, 1870-1890)
// note 1920: no apportionment

#ifndef METHODS_HPP
#define METHODS_HPP

#include "State.hpp"
#include "Apportionment.hpp"
#include <string>

/* Adams method: priority = population / curSeats
 * (floor)
 * considered 1830, not used
 * (most favorable to small states)
 */
double adams(const State &state);

/* Dean method: priority = population / harmonicMean(curSeats, curSeats + 1)
 * 
 * considered 1830, not used
 */
double dean(const State &state);

/* Huntington-Hill method:
 *
 * priority = population / geometricMean(curSeats, curSeats + 1)
 * used 1940 on
 */
double huntingtonHill(const State &state);

/* Webster method:
 *
 * priority = population / arithmeticMean(curSeats, curSeats + 1)
 * used 1840, 1910, 1930
 */
double webster(const State &state);

/* Jefferson method: priority = population / (curSeats + 1)
 * (ceiling)
 * used 1790-1830
 * (most favorable to large states)
 */
double jefferson(const State &state);

#endif
