#pragma once
#include "PxPhysicsAPI.h"
#include <extensions/PxDefaultAllocator.h>

class PhisycsEngine
{
public:
	PhisycsEngine();
	~PhisycsEngine();

public:
	static PhisycsEngine* get();
	static void create();
	static void release();

public:
	static physx::PxDefaultErrorCallback m_defaultErrorCallback;
	static physx::PxDefaultAllocator m_defaultAllocatorCallback;

	physx::PxFoundation* m_foundation;

private:
	static PhisycsEngine* m_engine;
};