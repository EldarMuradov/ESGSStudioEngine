#include "PhisycsEngine.h"
#include <exception>
#include <exception>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

PhisycsEngine* PhisycsEngine::m_engine = nullptr;

PhisycsEngine::PhisycsEngine()
{
	m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);

	if (!m_foundation)
		throw std::exception("Failed to create {PxFoundation}. Error in {PhysicsEngine} ctor.");
	m_pvd = PxCreatePvd(*m_foundation);

	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);

	m_pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	m_toleranceScale.length = 100;
	m_toleranceScale.speed = 981;

	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, m_toleranceScale, true, m_pvd);

	physx::PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	m_dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = m_dispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	m_scene = m_physics->createScene(sceneDesc);
}

PhisycsEngine* PhisycsEngine::get()
{
	return PhisycsEngine::m_engine;
}

void PhisycsEngine::create()
{
	if (PhisycsEngine::m_engine)
		throw std::exception("Failed to create {PhisycsEngine}. Error in {PhisycsEngine::create()}. {PhisycsEngine} is already created.");
	PhisycsEngine::m_engine = new PhisycsEngine();
}

void PhisycsEngine::release()
{
	if (!PhisycsEngine::m_engine)
		return;
	delete PhisycsEngine::m_engine;
}

PhisycsEngine::~PhisycsEngine()
{
	PhisycsEngine::m_engine = nullptr;
}