#ifndef METHODS_HPP
#define METHODS_HPP

#include "State.hpp"
#include <string>

class Adams : public State {
public:
  Adams();
  Adams(std::string stateName, unsigned long long statePopulation);
  ~Adams();
protected:
  double setPriority() override;
};

class Dean : public State {
public:
  Dean();
  Dean(std::string stateName, unsigned long long statePopulation);
  ~Dean();
protected:
  double setPriority() override;
};

class HuntingtonHill : public State {
public:
  HuntingtonHill();
  HuntingtonHill(std::string stateName, unsigned long long statePopulation);
  ~HuntingtonHill();
protected:
  double setPriority() override;
};

class Webster : public State {
public:
  Webster();
  Webster(std::string stateName, unsigned long long statePopulation);
  ~Webster();
protected:
  double setPriority() override;
};

class Jefferson : public State {
public:
  Jefferson();
  Jefferson(std::string stateName, unsigned long long statePopulation);
  ~Jefferson();
protected:
  double setPriority() override;
};

#endif
