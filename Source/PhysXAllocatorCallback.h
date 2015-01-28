#pragma once
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

using namespace physx;

class PhysXAllocatorCallback :
	public PxAllocatorCallback
{
public:
	PhysXAllocatorCallback();
	~PhysXAllocatorCallback();

	void* allocate(size_t size, const char*, const char*, int);
	void  deallocate(void* ptr);
};

