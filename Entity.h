#pragma once
#include "Prerequisites.h"

class Entity
{
public: 
	Entity();
	virtual ~Entity();
	void release();

protected:
	virtual void onCreate() 
	{
	
	}

protected:
	size_t m_type_id = 0;

	World* m_world = nullptr;

	friend class World;
};