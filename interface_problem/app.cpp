#include "A.h"

int main() {
  B *b = new B();

  call_f(b);

  delete b;
}