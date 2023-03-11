#pragma once
#include <Windows.h>
#include "GUIManager.h"

class Window
{
public:
	Window();

	bool isRun();

	RECT getClientWindowRect();
	RECT getSizeScreen();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();
	virtual void onSize();

	~Window();

private:
	bool broadcast();

protected:
	HWND m_hwnd;

	static bool m_play;

	GUIManager m_gui = GUIManager();

	bool m_is_run;
	bool m_is_init = false;
};