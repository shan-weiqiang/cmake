#include "Base.h"

void call_f(Base *b);

// Here we include B.h to inform the user of A that all the possible derived
// class of Base User should create object with thiese class and pass them into
// call_f, which does not depend on B at all, since A and call_f is just
// interface library. What A really does is just passing pointers.

// Of course, here user can intentionally include any header files and make A depend
// on those libraries in cmake with `target_link_libraries(A INTERFACE ...)`, even
// though that A does not use them in it's cpp file(only exist in API header file).
// This assures that any target linked to A will automatically find those headers and
// depend on those libraries.

#include "B.h"