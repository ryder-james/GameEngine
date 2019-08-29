#include "memory.h"

#include <iostream>

#include "heap.h"

heap g_main_heap;

void* operator new(size_t size) {
	return g_main_heap.allocate(size);
}

void operator delete(void* ptr, size_t size) {
	g_main_heap.free(ptr);
}

//void operator delete[](void* ptr, size_t size) {
//	g_main_heap.free(ptr);
//}
