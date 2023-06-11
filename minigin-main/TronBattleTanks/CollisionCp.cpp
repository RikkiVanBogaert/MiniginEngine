#include "CollisionCp.h"

#include "GameObject.h"

#include <glm/glm.hpp>

CollisionCp::CollisionCp(dae::GameObject* owner):
ComponentBase(owner)
{}

void CollisionCp::SetColliders(const std::vector<dae::GameObject*>& colliders)
{
	m_pColliders = colliders;
}

void CollisionCp::AddCollider(dae::GameObject* collider)
{
	m_pColliders.emplace_back(collider);
}

bool CollisionCp::CollisionHit(dae::GameObject* object, const glm::vec2& dir) const
{
	const auto objectPos = object->GetWorldTransform();
	const float objectSize = object->GetSize().x;
	constexpr float rayLength = 1;
	const glm::vec2 direction = normalize(dir) * rayLength;
	const glm::vec2 rayPoint = { objectPos.x + direction.x, objectPos.y + direction.y };

	for (const auto& collider : m_pColliders)
	{
		const auto colPos = collider->GetWorldTransform();
		const auto colSize = collider->GetSize().x;
		if(int(rayPoint.x) + objectSize > colPos.x && int(rayPoint.x) < colPos.x + colSize &&
			int(rayPoint.y) + objectSize > colPos.y && int(rayPoint.y) < colPos.y + colSize)
		{
			return true;
		}
	}


	return false;
}

bool CollisionCp::DoesOverlap(dae::GameObject* object) const
{
	//const float square1BottomRightX = object->GetWorldTransform().x + object->GetSize().x;
	//const float square1BottomRightY = object->GetWorldTransform().y + object->GetSize().y;

	//const float square2BottomRightX = m_pOwner->GetWorldTransform().x + m_pOwner->GetSize().x;
	//const float square2BottomRightY = m_pOwner->GetWorldTransform().y + m_pOwner->GetSize().y;

	//// Check for overlap
	//if (object->GetWorldTransform().x > square2BottomRightX || m_pOwner->GetWorldTransform().x > square1BottomRightX)
	//	return false; // Squares are horizontally separated

	//if (object->GetWorldTransform().y > square2BottomRightY || m_pOwner->GetWorldTransform().y > square1BottomRightY)
	//	return false; // Squares are vertically separated

	//return true; // Squares overlap

	const glm::vec2 objectPos = object->GetWorldTransform();
	const glm::vec2 objectSize = object->GetSize();
	const glm::vec2 ownerPos = GetOwner()->GetWorldTransform();
	const glm::vec2 ownerSize = GetOwner()->GetSize();

	if (objectPos.x + objectSize.x > ownerPos.x && objectPos.x < ownerPos.x + ownerSize.x &&
		objectPos.y + objectSize.y > ownerPos.y && objectPos.y < ownerPos.y + ownerSize.y)
	{
		return true;
	}

	return false;
}
