#include "ichneutae/memory/aligned_allocator.h"
#include <include/gtest/gtest.h>

namespace {
TEST(allocator, it_works) {
	auto ptr = in::memory::aligned_allocator<void>::operator new(10);
	in::memory::aligned_allocator<void>::operator delete(ptr, 10);
	//  ptr = in::memory::aligned_allocator<long>::operator new(sizeof(long));
	//  in::memory::aligned_allocator<long>::operator delete(ptr, sizeof(long));
}
} // namespace
