#include "Component.h"
#include "Entity.h"

Component::Component()
{
}

Component::~Component()
{
}

void Component::release()
{
	m_entity->removeComponent(m_type_id);
}

Entity* Component::getEntity()
{
	return m_entity;
}

void Component::onCreateInternal()
{

}
