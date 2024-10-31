#include "Base.h"
#include <iostream>

class B : public Base {
public:
  void f() override;
  virtual ~B() override;
};