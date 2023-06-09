#include "CollisionCp.h"
#include "GameObject.h"

CollisionCp::CollisionCp(dae::GameObject* owner):
ComponentBase(owner)
{}

void CollisionCp::SetColliders(std::vector<dae::GameObject*> colliders)
{
	m_pColliders = colliders;
}

void CollisionCp::AddCollider(dae::GameObject* collider)
{
	m_pColliders.emplace_back(collider);
}

bool CollisionCp::CollisionHit(dae::GameObject* object, const glm::vec2& dir)
{
	const auto objectPos = object->GetWorldTransform();
	const float objectSize = object->GetSize().x;
	const float rayLength = 1;
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

bool CollisionCp::DoesOverlap(dae::GameObject* object)
{
	const float square1BottomRightX = object->GetWorldTransform().x + object->GetSize().x;
	const float square1BottomRightY = object->GetWorldTransform().y + object->GetSize().y;

	const float square2BottomRightX = m_pOwner->GetWorldTransform().x + m_pOwner->GetSize().x;
	const float square2BottomRightY = m_pOwner->GetWorldTransform().y + m_pOwner->GetSize().y;

	// Check for overlap
	if (object->GetWorldTransform().x > square2BottomRightX || m_pOwner->GetWorldTransform().x > square1BottomRightX)
		return false; // Squares are horizontally separated

	if (object->GetWorldTransform().y > square2BottomRightY || m_pOwner->GetWorldTransform().y > square1BottomRightY)
		return false; // Squares are vertically separated

	return true; // Squares overlap
}
