#pragma once

#include <memory>
#include "Transform.h"

class GameObject;

class ComponentBase
{
public:
	ComponentBase() {};
	//virtual ~ComponentBase();

	/*ComponentBase(const ComponentBase& other) = delete;
	ComponentBase(ComponentBase&& other) = delete;
	ComponentBase& operator=(const ComponentBase& other) = delete;
	ComponentBase& operator=(ComponentBase&& other) = delete;*/


	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);
	virtual void Render() const;

protected:
	bool m_NeedsUpdate{ true };
	GameObject* m_pOwner{};

private:

	//------
	//make a render component which can be inhereted from by text, texture, line-rendering or somin, etc...
	//maybe dont use shared_ptr if there is no reason, use unique instead (idk bruh)
	//give components access to their owned gameObject
};

