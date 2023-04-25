#include "Bullet.h"

#include "TextureComponent.h"

Bullet::Bullet(glm::vec3 velocity):
	m_Velocity{velocity}
{
	//SetTag("bullet");

	auto blueTankTxt = std::make_shared<TextureComponent>(this);
	blueTankTxt->SetTexture("Resources/Sprites/BulletPlayer.png");
	AddComponent(blueTankTxt);
}

void Bullet::Update(float deltaTime)
{
	auto newPos = GetRelativeTransform() + m_Velocity * deltaTime;
	SetRelativePos(newPos);

	if (abs(GetWorldTransform().x) > 1000 ||
		abs(GetWorldTransform().y) > 1000)
	{
		//improve this, use actual windowSize
		MarkForDeletion();
	}
}
