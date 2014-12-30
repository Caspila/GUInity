#include "PhysXAllocatorCallback.h"


PhysXAllocatorCallback::PhysXAllocatorCallback()
{
}


PhysXAllocatorCallback::~PhysXAllocatorCallback()
{
}

void* PhysXAllocatorCallback::allocate(size_t size, const char*, const char*, int)
	{
		return _aligned_malloc(size, 16);
	}

void PhysXAllocatorCallback::deallocate(void* ptr)
	{
		_aligned_free(ptr);
	}