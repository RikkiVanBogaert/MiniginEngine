#include "Tank.h"

#include "TextureComponent.h"
#include "Scene.h"
#include "Bullet.h"

RedTank::RedTank()
{
	SetTag("redTank"); //make diff Tank prefabs

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

void RedTank::Update(float)
{
	CheckOverlap();
}

void RedTank::CheckOverlap()
{
	for (auto& o : GetScene()->GetGameObjects())
	{
		//if (typeid(o) != typeid(Bullet)) continue;
		if (o->GetTag() == GetTag()) continue;

		auto bulletPos = o->GetWorldTransform();

		if (bulletPos.x > GetWorldTransform().x && bulletPos.x < GetWorldTransform().x + GetSize().x &&
			bulletPos.y > GetWorldTransform().y && bulletPos.y < GetWorldTransform().y + GetSize().y)
		{
			//std::cout << "BULLET HIT\n";
			o->MarkForDeletion();
		}
	}
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

void BlueTank::Update(float)
{
	CheckOverlap();
}

void BlueTank::CheckOverlap()
{
	for (auto& o : GetScene()->GetGameObjects())
	{
		//if (typeid(o) != typeid(Bullet)) continue;
		if (o->GetTag() == GetTag()) continue;

		auto bulletPos = o->GetWorldTransform();

		if (bulletPos.x > GetWorldTransform().x && bulletPos.x < GetWorldTransform().x + GetSize().x &&
			bulletPos.y > GetWorldTransform().y && bulletPos.y < GetWorldTransform().y + GetSize().y)
		{
			//std::cout << "BULLET HIT\n";
			o->MarkForDeletion();
		}
	}
}