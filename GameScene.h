#pragma once
#include "Prerequisites.h"
#include "AppWindow.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	void awake();
	void start();
	void update();
	void editorUpdate();

public:
	AppWindow* m_level = nullptr;

	Entity* m_entity = nullptr;
};