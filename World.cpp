#include "World.h"
#include "Entity.h"
#include "CMesh.h"
#include <vector>
#include <string>
#include "Counter.h"

std::vector<Entity*> World::m_all;

World::World(GameScene* game)
{
	m_game = game;
}

World::~World()
{
	delete m_game;
	m_game = nullptr;
}

void World::update()
{
	for (auto entity : m_entities_to_destroy)
	{
		m_entities[entity->m_type_id].erase(entity);
		for (std::vector<Entity*>::iterator iter = m_all.begin(); iter != m_all.end(); ++iter)
		{
			if (*iter == entity)
			{
				m_all.erase(iter);
				break;
			}
		}
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

GameScene* World::getGame()
{
	return m_game;
}

const MaterialPtr& World::getSkyMat()
{
	return m_sky_mat;
}

void World::setSkyTexture(const wchar_t* path)
{
	TexturePtr tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(path);
	m_game->m_level->getSkyMaterial()->setSingleTexture(tex);
}

std::vector<Entity*> World::getAllEntities()
{
	return m_all;
}

void World::createEntityInternal(Entity* entity, size_t id)
{
	auto entityPtr = std::unique_ptr<Entity>(entity);

	m_entities[id].emplace(entity, std::move(entityPtr));
	entity->m_type_id = id;
	entity->m_world = this;
	entity->onCreate();

	m_all.push_back(entity);
}

void World::removeEntity(Entity* entity)
{
	m_entities_to_destroy.emplace(entity);
}
