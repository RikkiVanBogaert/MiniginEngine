#include "Tank.h"

#include "TextureComponent.h"
#include "Scene.h"
#include "Bullet.h"


void Tank::Update(float)
{
	CheckOverlap();
}

void Tank::CheckOverlap()
{
	for (auto& o : GetScene()->GetGameObjects())
	{
		if (!dynamic_cast<Bullet*>(o.get())) continue;
		if (o->GetTag() == GetTag()) continue;

		const auto bulletPos = o->GetWorldTransform();
		const auto bulletSize = o->GetSize();

		if (bulletPos.x + bulletSize.x > GetWorldTransform().x && bulletPos.x < GetWorldTransform().x + GetSize().x / 2 && //use / 2 otherwise hitbox too big
			bulletPos.y + bulletSize.y > GetWorldTransform().y && bulletPos.y < GetWorldTransform().y + GetSize().y / 1.6f) //same here
		{
			o->MarkForDeletion();
		}
	}
}


RedTank::RedTank()
{
	SetTag("redTank");

	auto blueTankTxt = std::make_shared<TextureComponent>(this);
	blueTankTxt->SetTexture("Resources/Sprites/RedTank.png");
	AddComponent(blueTankTxt);

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());
	gunTxt->SetTexture("Resources/Sprites/RedTankGun.png");
	SetSize(gunTxt->GetTextureSize());

	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8, 0 });
	AddChild(m_pGun.get());
}

BlueTank::BlueTank()
{
	SetTag("blueTank");

	auto blueTankTxt = std::make_shared<TextureComponent>(this);
	blueTankTxt->SetTexture("Resources/Sprites/BlueTank.png");
	AddComponent(blueTankTxt);

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());
	gunTxt->SetTexture("Resources/Sprites/BlueTankGun.png");
	SetSize(gunTxt->GetTextureSize());

	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8, 0 });
	AddChild(m_pGun.get());
}