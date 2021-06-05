/*
 * Concrete versions of the abstract Apportionment class representing
 * different priority functions used to decide which state gets the next
 * seat
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
 * 
 * considered 1830, not used
 */
class AdamsMethod : public Apportionment {
public:
  AdamsMethod();
  ~AdamsMethod();
protected:
  virtual double priority(const State &state) override;
};

/* Dean method: priority = population / harmonicMean(curSeats, curSeats + 1)
 * 
 * considered 1830, not used
 */
class DeanMethod : public Apportionment {
public:
  DeanMethod();
  ~DeanMethod();
protected:
  virtual double priority(const State &state) override;
};

/* Huntington-Hill method:
 *
 * priority = population / geometricMean(curSeats, curSeats + 1)
 * used 1940 - 2010
 */
class HuntingtonHillMethod : public Apportionment {
public:
  HuntingtonHillMethod();
  ~HuntingtonHillMethod();
protected:
  virtual double priority(const State &state) override;
};

/* Webster method:
 *
 * priority = population / arithmeticMean(curSeats, curSeats + 1)
 * used 1840, 1910, 1930
 */
class WebsterMethod : public Apportionment {
public:
  WebsterMethod();
  ~WebsterMethod();
protected:
  virtual double priority(const State &state) override;
};

/* Jefferson method: priority = population / (curSeats + 1)
 *
 * used 1790-1830
 */
class JeffersonMethod : public Apportionment {
public:
  JeffersonMethod();
  ~JeffersonMethod();
protected:
  virtual double priority(const State &state) override;
};

#endif
