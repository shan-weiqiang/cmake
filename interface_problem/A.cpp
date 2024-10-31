#include "A.h"
void call_f(Base *b) {
  // Possible complex operations here...
  // Only operate with pointers, no dereferencing here
  b->f();
}

// The implementation of A have nothing to do with B