#include "InputSystem.h"
#include <Windows.h>
#include "AppWindow.h"
#include "KeyCode.h"

InputSystem* InputSystem::m_system = nullptr;

bool m_l_b = false;
bool m_r_b = false;

InputSystem::InputSystem()
{
}

void InputSystem::update()
{
	key_up = 0;
	key_down = 0;

	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			m_mouse_pos = Vector2D((int)current_mouse_pos.x, (int)current_mouse_pos.y);

			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			lockCursorInternal();

			++it;
		}
	}
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
							m_l_b = true;
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
							m_r_b = true;
					}
					else
					{
						(*it)->onKeyDown(i);

						if (i == (int)KeyCode::W)
							y_axis = 1.0f;
						else if (i == (int)KeyCode::S)
							y_axis = -1.0f;

						if (i == (int)KeyCode::D)
							x_axis = 1.0f;
						else if (i == (int)KeyCode::A)
							x_axis = -1.0f;

						key_down = i;
					}
					++it;
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						if (i == VK_LBUTTON)
						{
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
							m_l_b = false;
						}
						else if (i == VK_RBUTTON)
						{
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
							m_r_b = false;
						}
						else
						{
							(*it)->onKeyUp(i);

							y_axis = 0.0f;
							x_axis = 0.0f;

							key_up = i;
						}

						++it;
					}
				}
			}
		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

void InputSystem::lockCursor(bool lock)
{
	m_lock_cursor = lock;
}

bool InputSystem::getMouseButton(int i)
{
	if (i == 0)
		return m_l_b;
	else if (i == 1)
		return m_r_b;

	return false;
}

Vector2D& InputSystem::getMousePosition()
{
	return m_mouse_pos;
}

bool InputSystem::isKeyDown(KeyCode code)
{
	if(key_down == (int)code)
		return true;
	return false;
}

bool InputSystem::isKeyUp(KeyCode code)
{
	if (key_up == (int)code)
		return true;
	return false;
}

float InputSystem::getAxisRaw(const char* type)
{
	if (type == "Horizontal")
		return x_axis;
	else if (type == "Vertical")
		return y_axis;
	return 0.0f;
}

InputSystem* InputSystem::get()
{
	return m_system;
}

void InputSystem::create()
{
	if (InputSystem::m_system) 
		throw std::exception("Failed to create {InputSystem}. {InputSystem} is already created.");
	InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
	if (!InputSystem::m_system) 
		return;
	delete InputSystem::m_system;
}

void InputSystem::lockCursorInternal()
{
	if (m_lock_cursor)
		InputSystem::get()->setCursorPosition(Point((int)(AppWindow::getRect().m_x / 2.0f), (int)(AppWindow::getRect().m_y / 2.0f)));
}

InputSystem::~InputSystem()
{
	InputSystem::m_system = nullptr;
}