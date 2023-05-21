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

	const glm::vec2 midPoint = { objectPos.x + object->GetSize().x / 2, objectPos.y + object->GetSize().y / 2 };
	const float rayLength = object->GetSize().x / 2;
	const float dirLength = sqrtf(dir.x * dir.x + dir.y * dir.y);
	const glm::vec2 normalizedDir = { dir.x / dirLength,  dir.y / dirLength };
	const glm::vec2 rayPoint = { midPoint.x + normalizedDir.x * rayLength, midPoint.y + normalizedDir.y * rayLength };

	for (const auto& collider : m_pColliders)
	{
		if (rayPoint.x >= collider->GetWorldTransform().x && rayPoint.x <= collider->GetWorldTransform().x + collider->GetSize().x &&
			rayPoint.y >= collider->GetWorldTransform().y && rayPoint.y <= collider->GetWorldTransform().y + collider->GetSize().y)
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
