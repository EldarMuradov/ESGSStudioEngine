#include "World.h"
#include "Entity.h"

World::World()
{
}

World::~World()
{
}

void World::update()
{
	for (auto entity : m_entities_to_destroy)
	{
		m_entities[entity->m_type_id].erase(entity);
	}
	m_entities_to_destroy.clear();

	for (auto&& [typeId, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			ptr->onUpdate();
		}
	}
}

void World::createEntityInternal(Entity* entity, size_t id)
{
	auto entityPtr = std::unique_ptr<Entity>(entity);

	m_entities[id].emplace(entity, std::move(entityPtr));
	entity->m_type_id = id;
	entity->m_world = this;
	entity->onCreate();
}

void World::removeEntity(Entity* entity)
{
	m_entities_to_destroy.emplace(entity);
}
