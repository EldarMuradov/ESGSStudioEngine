#include "PhysicsEngine.h"
#include <exception>
#include <exception>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include <iostream>

PhysicsEngine* PhysicsEngine::m_engine = nullptr;
physx::PxScene* PhysicsEngine::m_scene = NULL;

PhysicsEngine::PhysicsEngine()
{
	m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);

	if (!m_foundation)
		throw std::exception("Failed to create {PxFoundation}. Error in {PhysicsEngine} ctor.");
	m_pvd = PxCreatePvd(*m_foundation);

	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 100);
	//physx::PxPvdTransport* transport = physx::PxDefaultPvdFileTransportCreate("E:\\ESGS Studio Engine\\PVD\\pvd.pvd");
	if (transport == NULL)
		throw std::exception("Failed to create {PxPvdTransport}. Error in {PhysicsEngine} ctor.");

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

	physx::PxPvdSceneClient* client = m_scene->getScenePvdClient();

	std::cout << "PVD Conn: " << m_pvd->isConnected() << "\n";

	if (client)
	{
		client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	m_material = m_physics->createMaterial(0.5f, 0.5f, 0.6f);

	physx::PxRigidStatic* terrain = PxCreatePlane(*m_physics, physx::PxPlane(0, 1, 0, 99), *m_material);
	terrain->setGlobalPose(physx::PxTransform(0, 0, 0));
	terrain->setName("Terrain");
	//physx::PxRigidStatic* plane = PxCreatePlane(*m_physics, physx::PxPlane(0, 1, 0, 2), *m_material);
	
	m_scene->addActor(*terrain);
	//m_scene->addActor(*plane);
	std::cout << "Physics Actors: " << m_scene->getNbActors(physx::PxActorTypeFlag::eRIGID_STATIC) << "\n";
}

PhysicsEngine* PhysicsEngine::get()
{
	return PhysicsEngine::m_engine;
}

void PhysicsEngine::create()
{
	if (PhysicsEngine::m_engine)
		throw std::exception("Failed to create {PhisycsEngine}. Error in {PhisycsEngine::create()}. {PhisycsEngine} is already created.");
	PhysicsEngine::m_engine = new PhysicsEngine();
}

void PhysicsEngine::release()
{
	if (!PhysicsEngine::m_engine)
		return;
	delete PhysicsEngine::m_engine;
}

PhysicsEngine::~PhysicsEngine()
{
	/*m_material->release();
	m_foundation->release();
	m_dispatcher->release();
	m_scene->release();
	m_pvd->disconnect();
	m_pvd->release();
	m_physics->release();*/
	PhysicsEngine::m_engine = nullptr;
}