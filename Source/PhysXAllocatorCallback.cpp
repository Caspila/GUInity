#include "PhysXAllocatorCallback.h"
#include <stdlib.h>





PhysXAllocatorCallback::PhysXAllocatorCallback()
{
}


PhysXAllocatorCallback::~PhysXAllocatorCallback()
{
}

void* PhysXAllocatorCallback::allocate(size_t size, const char*, const char*, int)
{
#ifdef _WIN32 // note the underscore: without it, it's not msdn official!
    // Windows (x64 and x86)
    return _aligned_malloc(size, 16);
#elif __APPLE__
    return malloc(size);
    // Mac OS, not sure if this is covered by __posix__ and/or __unix__ though...
#endif
		
	}

void PhysXAllocatorCallback::deallocate(void* ptr)
	{
        
#ifdef _WIN32 // note the underscore: without it, it's not msdn official!
        // Windows (x64 and x86)
		_aligned_free(ptr);
#elif __APPLE__
        delete ptr;
        // Mac OS, not sure if this is covered by __posix__ and/or __unix__ though...
#endif
	}