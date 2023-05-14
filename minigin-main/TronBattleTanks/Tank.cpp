#include "Tank.h"

#include "AIComponent.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "Bullet.h"

#include "AudioService.h"
#include "EventQueue.h"
#include "MyEvents.h"
#include "Sounds.h"

using namespace dae;

void Tank::Update(float deltaTime)
{
	CheckOverlap();
	GameObject::Update(deltaTime);
}

void Tank::ShootBullet(const glm::vec2& direction)
{
	auto& event_queue = EventQueue<MyEvent, double>::GetInstance();
	event_queue.schedule(MyEvent(1, 0), 0.0);


	const auto bullet = std::make_shared<Bullet>(direction);
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