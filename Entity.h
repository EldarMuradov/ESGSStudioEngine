#pragma once
#include "Prerequisites.h"
#include <map>
#include <vector>
#include "Component.h"
#include "ESGSStudioEngine.h"
#include "InputSystem.h"

class Entity
{
public: 
	Entity();
	virtual ~Entity();
	void release();

	World* getWorld();
	CTransform* getTransform();

	void setName(const char* name);
	const char* getName();

	void setTag(const char* tag);
	const char* getTag();

	InputSystem* getInputSystem();

	template<typename T>
	T* createComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Your TYPE must be derive from {Component}");

		auto comp = getComponent<T>();
		if (comp)
			return nullptr;

		auto id = typeid(T).hash_code();

		auto component = new T();
		createComponentInternal(component, id);
		return component;
	}

	template<typename T>
	T* getComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Your TYPE must be derive from {Component}");
		auto id = typeid(T).hash_code();

		return (T*)getComponentInternal(id);
	}

private:
	Component* getComponentInternal(size_t id);
	void createComponentInternal(Component* component, size_t id);
	void removeComponent(size_t id);

	std::vector<Component*> getAllComponentsFromEntity();

protected:
	virtual void onCreate() 
	{
	
	}

	virtual void onUpdate() 
	{
	
	}

protected:
	size_t m_type_id = 0;

	World* m_world = nullptr;

	CTransform* m_transform = nullptr;

	std::map<size_t, std::unique_ptr<Component>> m_components;

	std::vector<Component*> m_internal_comp;

	const char* m_name = "Entity";
	const char* m_tag = "Default";

	friend class World;
	friend class InspectorTool;
	friend class Component;
};