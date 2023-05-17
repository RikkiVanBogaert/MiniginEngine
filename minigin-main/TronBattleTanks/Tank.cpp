#include "Tank.h"

#include <SDL_pixels.h>

#include "AIComponent.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "Bullet.h"

#include "Sounds.h"
#include "EventQueue.h"
#include "EngineEvents.h"
#include "GameEvents.h"
#include "ResourceManager.h"
#include "UICp.h"

using namespace dae;

Tank::Tank(Type type):
	m_Type(type)
{
	auto tankTxt = std::make_shared<TextureComponent>(this);

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());

	switch (m_Type)
	{
	case Red:
		SetTag("Red");
		tankTxt->SetTexture("Resources/Sprites/RedTank.png");
		gunTxt->SetTexture("Resources/Sprites/RedTankGun.png");
		break;

	case Blue:
		SetTag("Blue");
		tankTxt->SetTexture("Resources/Sprites/BlueTank.png");
		gunTxt->SetTexture("Resources/Sprites/BlueTankGun.png");
		break;
	}

	AddComponent(tankTxt);
	SetSize(tankTxt->GetTextureSize());

	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8 });
	AddChild(m_pGun);
}

void Tank::InitType()
{
	//use this to switch from red to blue tank
}

void Tank::Update(float deltaTime)
{
	CheckOverlap();
	GameObject::Update(deltaTime);
}

void Tank::ShootBullet(const glm::vec2& )
{
	/*auto& event_queue = EventQueue<Event, float>::GetInstance();
	event_queue.schedule(SoundEvent(1, Shoot), 0);
	
	const auto bullet = std::make_shared<Bullet>(this, direction);
	bullet->SetTag(GetTag());

	const glm::vec2 middlePos = { GetWorldTransform().x + GetSize().x / 2 - bullet->GetSize().x / 2,
		GetWorldTransform().y + GetSize().y / 2 - bullet->GetSize().y / 2};
	bullet->SetRelativePos(middlePos);

	GetScene()->Add(bullet);*/
}


void Tank::CheckOverlap()
{
	for (auto& o : GetScene()->GetGameObjects())
	{
		if (o->NeedsDeleting()) return;
		if (!dynamic_cast<Bullet*>(o.get())) continue;
		if (o->GetTag() == GetTag()) continue;

		const auto bulletPos = o->GetWorldTransform();
		const auto bulletSize = o->GetSize();

		if (bulletPos.x + bulletSize.x > GetWorldTransform().x && bulletPos.x < GetWorldTransform().x + GetSize().x / 2 && //use / 2 otherwise hitbox too big
			bulletPos.y + bulletSize.y > GetWorldTransform().y && bulletPos.y < GetWorldTransform().y + GetSize().y / 1.6f) //same here
		{
			auto pBullet = dynamic_cast<Bullet*>(o.get());

			auto& event_queue = EventQueue<Event, float>::GetInstance();
			event_queue.schedule(UpdateCounterEvent(1, pBullet->GetShooter(), 1), 0.0);
			//shoud only make the updateCounterEvent once and then just call it
			//Cant since using current bullet in event

			o->MarkForDeletion();
			GetHit();
		}
	}
}


PlayerTank::PlayerTank(Type type):
	Tank(type)
{
	/*SetTag("PlayerTank");

	auto redTankTxt = std::make_shared<TextureComponent>(this);
	redTankTxt->SetTexture("Resources/Sprites/RedTank.png");
	AddComponent(redTankTxt);
	SetSize(redTankTxt->GetTextureSize());

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());
	gunTxt->SetTexture("Resources/Sprites/RedTankGun.png");

	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8 });
	AddChild(m_pGun.get());*/

	m_pHealth = std::make_shared<dae::HealthCp>(this, 3);
	AddComponent(m_pHealth);

	const auto pPoints = std::make_shared<PointsCp>(this, 0);
	AddComponent(pPoints);
}

void PlayerTank::GetHit()
{
	m_pHealth->ChangeAmount(-1);
}


EnemyTank::EnemyTank():
	Tank(Blue)
{
	/*SetTag("EnemyTank");

	auto blueTankTxt = std::make_shared<TextureComponent>(this);
	blueTankTxt->SetTexture("Resources/Sprites/EnemyTank.png");
	AddComponent(blueTankTxt);
	SetSize(blueTankTxt->GetTextureSize());

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());
	gunTxt->SetTexture("Resources/Sprites/BlueTankGun.png");

	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8 });
	AddChild(m_pGun.get());*/

	m_pHealth = std::make_shared<dae::HealthCp>(this, 3);
	AddComponent(m_pHealth);

	m_pAICp = std::make_shared<AIComponent>(this);
	AddComponent(m_pAICp);
}

void EnemyTank::GetHit()
{
	m_pHealth->ChangeAmount(-1);
}