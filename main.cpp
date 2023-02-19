#include "AppWindow.h"
#include "InputSystem.h"
#include <exception>
#include "PhysicsEngine.h"

int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
		PhysicsEngine::create();
	}
	catch (...)
	{
		throw std::exception("Failed to create {GraphicsEngine} and {InputSystem}. Erorr in {main()}.");
		return -1;
	}

	try
	{
		AppWindow app;
		while (app.isRun());
	}
	catch (...)
	{
		throw std::exception("Failed to create a frame. Erorr in {AppWindow} pipeline.");
		InputSystem::release();
		GraphicsEngine::release();
		PhysicsEngine::release();
		return -1;
	}
	
	InputSystem::release();
	GraphicsEngine::release();
	PhysicsEngine::release();

	return 0;
}