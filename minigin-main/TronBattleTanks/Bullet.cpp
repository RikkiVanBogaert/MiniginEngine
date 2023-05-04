#include "Bullet.h"

#include "TextureComponent.h"

using namespace dae;

Bullet::Bullet(glm::vec3 velocity):
	m_Velocity{velocity}
{
	//SetTag("bullet");

	auto bulletTxt = std::make_shared<TextureComponent>(this);
	bulletTxt->SetTexture("Resources/Sprites/BulletPlayer.png");
	AddComponent(bulletTxt);

	SetSize(bulletTxt->GetTextureSize());
}

void Bullet::Update(float deltaTime)
{
	auto newPos = GetRelativeTransform() + m_Velocity * deltaTime;
	SetRelativePos(newPos);

	

	if (abs(GetWorldTransform().x) > 800 ||
		abs(GetWorldTransform().y) > 800)
	{
		//improve this, use actual windowSize
		MarkForDeletion();
	}
}

void Bullet::SetVelocity(glm::vec3 newVel)
{
	//if vel changed, that means we bounced
	++m_NrBounces;
	if (m_NrBounces >= 5)
	{
		MarkForDeletion();
		return;
	}

	m_Velocity = newVel;
}
