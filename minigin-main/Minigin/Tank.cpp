#include "Tank.h"

#include "TextureComponent.h"
#include "Scene.h"
#include "Bullet.h"

Tank::Tank()
{
	SetTag("redTank"); //make diff Tank prefabs

	auto blueTankTxt = std::make_shared<TextureComponent>(this);
	blueTankTxt->SetTexture("Resources/Sprites/RedTank.png");
	AddComponent(blueTankTxt);

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());
	gunTxt->SetTexture("Resources/Sprites/RedTankGun.png");
	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8, 0 });
	AddChild(m_pGun.get());
}

void Tank::Update(float)
{
	//RotateGun(deltaTime);
}

void Tank::CheckOverlap()
{
	for (auto o : GetScene()->GetGameObjects())
	{
		if (typeid(o) != typeid(Bullet)) return;

		//if(o->GetWorldTransform().x )
	}
}

void Tank::RotateGun(float deltaTime)
{
	float x{ m_pGun->GetRelativeTransform().x };
	float y{ m_pGun->GetRelativeTransform().y };

	rotateObject(x, y, 10 * deltaTime);

	m_pGun->SetRelativePos({ x, y, 0 });
	
}

void Tank::rotateObject(float& x, float& y, float angle) 
{
	float s = sin(angle);
	float c = cos(angle);
	float newX = x * c - y * s;
	float newY = x * s + y * c;
	x = newX;
	y = newY;
}