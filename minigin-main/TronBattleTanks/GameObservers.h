#pragma once
#include "GameObserverEvents.h"
#include "Observers.h"
#include "UICp.h"

namespace dae
{
	class GameObject;
}

class LivesObserver : public dae::Observer
{
public:
	LivesObserver(LivesCp* livesCp, dae::UILivesCp* UILivesCp) :
		m_pLivesCp(livesCp), m_pUILivesCp(UILivesCp)
	{}

	virtual ~LivesObserver() override = default;

	LivesObserver(const LivesObserver& other) = delete;
	LivesObserver(LivesObserver&& other) = delete;
	LivesObserver& operator=(const LivesObserver& other) = delete;
	LivesObserver& operator=(LivesObserver&& other) = delete;

	void Update(std::shared_ptr<ObserverEvent> event) override
	{
		//m_pLivesCp->ChangeAmount(-1);
		if (!dynamic_cast<PlayerHit*>(event.get())) return;
		
		m_pUILivesCp->SetValueText(std::to_string(m_pLivesCp->GetAmount()));
	}

private:
	LivesCp* m_pLivesCp{};
	dae::UILivesCp* m_pUILivesCp{};
};

class PointsObserver : public dae::Observer
{
public:
	PointsObserver(PointsCp* livesCp, dae::UIPointsCp* UILivesCp) :
		m_pPointsCp(livesCp), m_pUIPointsCp(UILivesCp)
	{}
	virtual ~PointsObserver() override = default;

	PointsObserver(const PointsObserver& other) = delete;
	PointsObserver(PointsObserver&& other) = delete;
	PointsObserver& operator=(const PointsObserver& other) = delete;
	PointsObserver& operator=(PointsObserver&& other) = delete;

	void Update(std::shared_ptr<ObserverEvent> event) override
	{
		if (dynamic_cast<BlueTankKilled*>(event.get()))
		{
			m_pPointsCp->ChangeAmount(100);
		}
		else if (dynamic_cast<RecognizerKilled*>(event.get()))
		{
			m_pPointsCp->ChangeAmount(250);
		}
		m_pUIPointsCp->SetValueText(std::to_string(m_pPointsCp->GetAmount()));
	}

private:
	PointsCp* m_pPointsCp{};
	dae::UIPointsCp* m_pUIPointsCp{};
};