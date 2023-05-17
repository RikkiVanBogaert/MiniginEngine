#include "BaseComponent.h"

using namespace dae;

ComponentBase::ComponentBase(GameObject* owner):
m_pOwner(owner)
{
}

void ComponentBase::Update(float)
{}

void ComponentBase::FixedUpdate(float)
{}

void ComponentBase::Render() const
{}
