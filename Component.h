#pragma once
#include "Prerequisites.h"

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void onUpdate() 
	{
	
	}

	virtual const char* toStr() 
	{
		return "Component";
	}

	void release();

	Entity* getEntity();

protected:
	virtual void onCreateInternal();

protected:
	size_t m_type_id = 0;

	Entity* m_entity = nullptr;

	friend class Entity;
};

