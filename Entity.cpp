#include "Entity.h"
#include "World.h"
#include "Component.h"
#include "ESGSStudioEngine.h"

Entity::Entity()
{
	m_transform = createComponent<CTransform>();
}

Entity::~Entity()
{
}

void Entity::release()
{
	m_world->removeEntity(this);
}

World* Entity::getWorld()
{
	return m_world;
}

CTransform* Entity::getTransform()
{
	return m_transform;
}

InputSystem* Entity::getInputSystem()
{
	return InputSystem::get();
}

Component* Entity::getComponentInternal(size_t id)
{
	auto comp = m_components.find(id);
	if(comp == m_components.end())
		return nullptr;
	return comp->second.get();
}

void Entity::createComponentInternal(Component* component, size_t id)
{
	auto compPtr = std::unique_ptr<Component>(component);

	m_components.emplace(id, std::move(compPtr));
	component->m_type_id = id;
	component->m_entity = this;

	component->onCreateInternal();
}

void Entity::removeComponent(size_t id)
{
	m_components.erase(id);
}
