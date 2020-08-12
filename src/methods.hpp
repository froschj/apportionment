#ifndef METHODS_HPP
#define METHODS_HPP

#include "State.hpp"
#include "Apportionment.hpp"
#include <string>

class Adams : public Apportionment {
public:
  Adams();
  ~Adams();
protected:
  double priority(State state) override;
};

class Dean : public Apportionment {
public:
  Dean();
  ~Dean();
protected:
  double priority(State state) override;
};

class HuntingtonHill : public Apportionment {
public:
  HuntingtonHill();
  ~HuntingtonHill();
protected:
  double priority(State state) override;
};

class Webster : public Apportionment {
public:
  Webster();
  ~Webster();
protected:
  double priority(State state) override;
};

class Jefferson : public Apportionment {
public:
  Jefferson();
  ~Jefferson();
protected:
  double priority(State state) override;
};

#endif
