#include "Entity.h"
#include "World.h"
#include "Component.h"
#include "ESGSStudioEngine.h"
#include <string>
#include "Counter.h"

Entity::Entity()
{
	m_transform = createComponent<CTransform>();
	m_name = "Entity (" + std::to_string(Counter::getCount()) + ")";
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

void Entity::setName(std::string name)
{
	m_name = name;
}

std::string Entity::getName()
{
	return m_name;
}

void Entity::setTag(const char* tag)
{
	m_tag = tag;
}

const char* Entity::getTag()
{
	return m_tag;
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

	m_internal_comp.push_back(component);
}

void Entity::removeComponent(size_t id)
{
	m_components.erase(id);
	auto comp = m_components.find(id)->second.get();
	for (std::vector<Component*>::iterator iter = m_internal_comp.begin(); iter != m_internal_comp.end(); ++iter)
	{
		if (*iter == comp)
		{
			m_internal_comp.erase(iter);
			break;
		}
	}
}

std::vector<Component*> Entity::getAllComponentsFromEntity()
{
	return m_internal_comp;
}
