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

void Tank::Update(float deltaTime)
{
	CheckOverlap();
	GameObject::Update(deltaTime);
}

void Tank::ShootBullet(const glm::vec2& direction)
{
	auto& event_queue = EventQueue<Event, float>::GetInstance();
	event_queue.schedule(SoundEvent(1, Shoot), 0);
	//event_queue.schedule(UpdateCounterEvent(1, this, 1), 0.0);

	const auto bullet = std::make_shared<Bullet>(this, direction);
	bullet->SetTag(GetTag());

	const glm::vec2 middlePos = { GetWorldTransform().x + GetSize().x / 2 - bullet->GetSize().x / 2,
		GetWorldTransform().y + GetSize().y / 2 - bullet->GetSize().y / 2};
	bullet->SetRelativePos(middlePos);

	GetScene()->Add(bullet);
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


RedTank::RedTank()
{
	SetTag("RedTank");

	auto redTankTxt = std::make_shared<TextureComponent>(this);
	redTankTxt->SetTexture("Resources/Sprites/RedTank.png");
	AddComponent(redTankTxt);
	SetSize(redTankTxt->GetTextureSize());

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());
	gunTxt->SetTexture("Resources/Sprites/RedTankGun.png");

	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8 });
	AddChild(m_pGun.get());

	m_pHealth = std::make_shared<dae::HealthCp>(this, 3);
	AddComponent(m_pHealth);

	const auto pPoints = std::make_shared<PointsCp>(this, 0);
	AddComponent(pPoints);

	////HUD
	//auto fontTankUI = ResourceManager::GetInstance().LoadFont("Lingua.otf", 60);
	//m_pPointText = std::make_shared<GameObject>("blueTank");
	////auto textBluePoints = std::make_shared<UICp>(fontTankUI, "Points: ", SDL_Color{ 0, 0, 255 },
	////	"Points", m_pPointText.get());
	//auto text = std::make_shared<TextComponent>(this, "TEXT", fontTankUI, SDL_Color{1,1,1,1});
	//m_pPointText->SetRelativePos({ 0, 0 });
	//m_pPointText->AddComponent(text);
	//AddChild(m_pPointText.get());
}

void RedTank::GetHit()
{
	m_pHealth->ChangeAmount(-1);
}


BlueTank::BlueTank()
{
	SetTag("BlueTank");

	auto blueTankTxt = std::make_shared<TextureComponent>(this);
	blueTankTxt->SetTexture("Resources/Sprites/BlueTank.png");
	AddComponent(blueTankTxt);
	SetSize(blueTankTxt->GetTextureSize());

	m_pGun = std::make_shared<GameObject>();
	auto gunTxt = std::make_shared<TextureComponent>(m_pGun.get());
	gunTxt->SetTexture("Resources/Sprites/BlueTankGun.png");

	m_pGun->AddComponent(gunTxt);
	m_pGun->SetRelativePos({ -10, -8 });
	AddChild(m_pGun.get());

	m_pHealth = std::make_shared<dae::HealthCp>(this, 3);
	AddComponent(m_pHealth);

	m_pAICp = std::make_shared<AIComponent>(this);
	AddComponent(m_pAICp);
}

void BlueTank::GetHit()
{
	m_pHealth->ChangeAmount(-1);
}