#pragma once
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

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
	physx::PxDefaultErrorCallback m_defaultErrorCallback;
	physx::PxDefaultAllocator m_defaultAllocatorCallback;

	physx::PxTolerancesScale m_toleranceScale;

	physx::PxFoundation* m_foundation = NULL;
	physx::PxPhysics* m_physics = NULL;
	physx::PxDefaultCpuDispatcher* m_dispatcher = NULL;

	physx::PxScene* m_scene = NULL;
	physx::PxMaterial* m_material = NULL;

	physx::PxPvd* m_pvd = NULL;

private:
	static PhisycsEngine* m_engine;
};