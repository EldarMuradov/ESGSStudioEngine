#pragma once
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

public:
	static PhysicsEngine* get();
	static void create();
	static void release();

public:
	static physx::PxScene* m_scene;
	physx::PxPvd* m_pvd;

	physx::PxFoundation* m_foundation;
	physx::PxPhysics* m_physics;

	physx::PxDefaultErrorCallback m_defaultErrorCallback;
	physx::PxDefaultAllocator m_defaultAllocatorCallback;

	physx::PxTolerancesScale m_toleranceScale;

	physx::PxDefaultCpuDispatcher* m_dispatcher = NULL;

	physx::PxMaterial* m_material = NULL;

private:
	static PhysicsEngine* m_engine;
};