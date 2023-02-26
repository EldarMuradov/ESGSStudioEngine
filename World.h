#pragma once
#include <map>
#include "Entity.h"
#include "Prerequisites.h"
#include <set>

class World
{
public:
	World();
	~World();

	template<typename T>
	T* createEntity() 
	{
		static_assert(std::is_base_of<Entity, T>::value, "Your TYPE must be derive from {Entity}");
		auto id = typeid(T).hash_code();

		auto entity = new T();
		createEntityInternal(entity, id);
		return entity;
	}

	void update();

private:
	void createEntityInternal(Entity* entity, size_t id);
	void removeEntity(Entity* entity);
private:
	std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> m_entities;
	std::set<Entity*> m_entities_to_destroy;

	friend class Entity;
};