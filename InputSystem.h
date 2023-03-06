#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"
#include "Vector2D.h"

class InputSystem
{
private:
	InputSystem();
	~InputSystem();

public:
	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void setCursorPosition(const Point& pos);
	void showCursor(bool show);
	void lockCursor(bool lock);
	Vector2D& getMousePosition();

public:
	static InputSystem* get();
	static void create();
	static void release();

private:
	void lockCursorInternal();

private:	
	Vector2D m_mouse_pos = Vector2D(0, 0);

	std::unordered_set<InputListener*> m_set_listeners;

	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};

	Point m_old_mouse_pos;

	bool m_first_time = true;
	bool m_lock_cursor = true;

	static InputSystem* m_system;
};