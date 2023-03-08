#include "PlayerController.h"
#include "ESGSStudioEngine.h"
#include <iostream>

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::onCreate()
{
	Entity::onCreate();

	createComponent<CCamera>();

	InputSystem::get()->lockCursor(true);
	InputSystem::get()->showCursor(false);

	getTransform()->isCamera(true);

	getTransform()->setPosition(Vector3D(0, 0, -10.0f));
}

void PlayerController::onUpdate()
{
	Entity::onUpdate();

	auto transform = getTransform();

	if (InputSystem::get()->isKeyDown(KeyCode::Escape))
	{
		m_locked = !m_locked;
		InputSystem::get()->lockCursor(m_locked);
		InputSystem::get()->showCursor(!m_locked);
		Sleep(100);
	}

	if (m_locked)
	{
		auto deltaPos = getInputSystem()->getMousePosition();

		int width = AppWindow::getRect().m_x;
		int height = AppWindow::getRect().m_y;

		if (m_delta_x != deltaPos.m_x || m_delta_y != deltaPos.m_y)
		{
			m_rot_x += (deltaPos.m_y - (height / 2.0f)) * AppWindow::getDeltaTime() * 0.1f;
			m_rot_y += (deltaPos.m_x - (width / 2.0f)) * AppWindow::getDeltaTime() * 0.1f;

			Vector2D rot = Vector2D(m_rot_x, m_rot_y);

			getTransform()->setCamRotation(rot);
		}

		m_delta_x = deltaPos.m_x;
		m_delta_y = deltaPos.m_y;

		auto pos = transform->getPosition();
		pos = pos + transform->getZDirection() * InputSystem::get()->getAxisRaw("Vertical") * 4.0f * AppWindow::getDeltaTime();
		pos = pos + transform->getXDirection() * InputSystem::get()->getAxisRaw("Horizontal") * 4.0f * AppWindow::getDeltaTime();

		transform->setPosition(pos);
	}
}