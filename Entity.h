#pragma once
#include "Prerequisites.h"
#include <map>
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

	friend class World;
	friend class Component;
};