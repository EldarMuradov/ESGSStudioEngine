#include "PhisycsEngine.h"
#include <exception>
#include <exception>
#include "PxPhysicsAPI.h"
#include <PxPhysicsAPI.h> 

/*#ifdef _DEBUG
#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PxTask.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PhysX3CharacterKinematicDEBUG_x86")
#else
#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PxTask.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#pragma comment(lib, "PhysX3CharacterKinematic_x86")
#endif*/

PhisycsEngine* PhisycsEngine::m_engine = nullptr;

PhisycsEngine::PhisycsEngine()
{
	m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);

	//if (!m_foundation)
		//throw std::exception("Failed to create {PxFoundation}. Error in {PhysicsEngine} ctor.");
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