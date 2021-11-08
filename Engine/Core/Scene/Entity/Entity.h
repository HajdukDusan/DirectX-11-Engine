#ifndef _ENTITY_H_
#define _ENTITY_H_

#pragma once
#include <unordered_set>

#include "Transform.h"
#include "Component.h"

class Entity
{
public:
	const char* m_Name;
	Transform* m_Transform;
	std::unordered_set<Component*> m_Components;

	Entity()
	{
		m_Name = "GameObject";
		m_Transform = new Transform();
	}

	Entity(const char* name, Transform* transform)
	{
		m_Name = name;
		m_Transform = transform;
	}

	~Entity()
	{
		delete m_Transform;
		for(Component* comp : m_Components)
		{
			delete comp;
		}
		m_Components.clear();
	}
};

#endif