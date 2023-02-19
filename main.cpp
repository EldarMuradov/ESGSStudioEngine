#include "AppWindow.h"
#include "InputSystem.h"
#include <exception>
#include "PhisycsEngine.h"

int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
		PhisycsEngine::create();
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
		PhisycsEngine::release();
		return -1;
	}
	
	InputSystem::release();
	GraphicsEngine::release();
	PhisycsEngine::release();

	return 0;
}