#pragma once
#include "GameObserverEvents.h"
#include "Observers.h"
#include "PointsCp.h"
#include "PlayerLivesCp.h"
#include "UICp.h"

namespace dae
{
	class GameObject;
}

class LivesObserver : public dae::Observer
{
public:
	LivesObserver(PlayerLivesCp* livesCp, UILivesCp* UILivesCp) :
		m_pLivesCp(livesCp), m_pUILivesCp(UILivesCp)
	{}

	virtual ~LivesObserver() override = default;

	LivesObserver(const LivesObserver& other) = delete;
	LivesObserver(LivesObserver&& other) = delete;
	LivesObserver& operator=(const LivesObserver& other) = delete;
	LivesObserver& operator=(LivesObserver&& other) = delete;

	void OnNotify(std::shared_ptr<ObserverEvent> event) override
	{
		if (!dynamic_cast<PlayerHitEvent*>(event.get())) return;

		m_pLivesCp->ChangeAmount(-1);
		m_pUILivesCp->SetValueText(std::to_string(m_pLivesCp->GetAmount()));
	}

private:
	PlayerLivesCp* m_pLivesCp{};
	UILivesCp* m_pUILivesCp{};
};

class PointsObserver : public dae::Observer
{
public:
	PointsObserver(PointsCp* livesCp, UIPointsCp* UILivesCp) :
		m_pPointsCp(livesCp), m_pUIPointsCp(UILivesCp)
	{}
	virtual ~PointsObserver() override = default;

	PointsObserver(const PointsObserver& other) = delete;
	PointsObserver(PointsObserver&& other) = delete;
	PointsObserver& operator=(const PointsObserver& other) = delete;
	PointsObserver& operator=(PointsObserver&& other) = delete;

	void OnNotify(std::shared_ptr<ObserverEvent> event) override
	{
		if (dynamic_cast<BlueTankKilledEvent*>(event.get()))
		{
			m_pPointsCp->GetCounter()->ChangeAmount(100);
		}
		else if (dynamic_cast<RecognizerKilledEvent*>(event.get()))
		{
			m_pPointsCp->GetCounter()->ChangeAmount(250);
		}
		m_pUIPointsCp->SetValueText(std::to_string(m_pPointsCp->GetCounter()->GetAmount()));
	}

private:
	PointsCp* m_pPointsCp{};
	UIPointsCp* m_pUIPointsCp{};
};