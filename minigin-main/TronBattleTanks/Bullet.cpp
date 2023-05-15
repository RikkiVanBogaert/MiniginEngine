#include "Bullet.h"

#include "TextureComponent.h"

using namespace dae;

Bullet::Bullet(Tank* shooter, glm::vec2 velocity):
	m_pShooter(shooter), m_Velocity{velocity}
{
	const auto bulletTxt = std::make_shared<TextureComponent>(this);
	bulletTxt->SetTexture("Resources/Sprites/BulletPlayer.png");
	AddComponent(bulletTxt);

	SetSize(bulletTxt->GetTextureSize());
}

void Bullet::Update(float deltaTime)
{
	const auto newPos = GetRelativeTransform() + m_Velocity * deltaTime;
	SetRelativePos(newPos);

}

void Bullet::SetVelocity(glm::vec2 newVel)
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
