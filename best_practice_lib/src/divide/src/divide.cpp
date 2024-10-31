#include "divide/divide.h"

namespace math {
float divide(float a, float b) { return a / b; }
} // namespace math

/** Following code coming from https://github.com/foonathan/memory, make this
 * lib depend on foonatham*/

#include <iostream>

#include <foonathan/memory/container.hpp>   // vector, list, list_node_size
#include <foonathan/memory/memory_pool.hpp> // memory_pool
#include <foonathan/memory/smart_ptr.hpp>   // allocate_unique
#include <foonathan/memory/static_allocator.hpp> // static_allocator_storage, static_block_allocator
#include <foonathan/memory/temporary_allocator.hpp> // temporary_allocator

// alias namespace foonathan::memory as memory for easier access
#include <foonathan/memory/namespace_alias.hpp>

void depend_dummy_function() {
  using namespace memory::literals;

  // a memory pool RawAllocator
  // allocates a memory block - initially 4KiB - and splits it into chunks of
  // list_node_size<int>::value big list_node_size<int>::value is the size of
  // each node of a std::list
  memory::memory_pool<> pool(memory::list_node_size<int>::value, 4_KiB);

  // just an alias for std::list<int, memory::std_allocator<int,
  // memory::memory_pool<>> a std::list using a memory_pool std_allocator stores
  // a reference to a RawAllocator and provides the Allocator interface
  memory::list<int, memory::memory_pool<>> list(pool);
  list.push_back(3);
  list.push_back(2);
  list.push_back(1);

  for (auto e : list)
    std::cout << e << ' ';
  std::cout << '\n';
}
