#include "Entity.h"
#include "World.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::release()
{
	m_world->removeEntity(this);
}
