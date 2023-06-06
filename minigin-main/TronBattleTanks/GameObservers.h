#pragma once
#include "Observers.h"
#include "UICp.h"

namespace dae
{
	class GameObject;
}

// Concrete observer classes
class LivesObserver : public dae::Observer
{
public:
	LivesObserver(LivesCp* livesCp, dae::UILivesCp* UILivesCp) :
		m_pLivesCp(livesCp), m_pUILivesCp(UILivesCp)
	{}
	void Update(dae::ObserverEvent event) override
	{
		//m_pLivesCp->ChangeAmount(-1);
		if (event != dae::PlayerHit) return;

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
	void Update(dae::ObserverEvent event) override
	{
		if (event == dae::BlueTankKilled)
		{
			m_pPointsCp->ChangeAmount(100);
		}
		else if (event == dae::RecognizerKilled)
		{
			m_pPointsCp->ChangeAmount(250);
		}
		m_pUIPointsCp->SetValueText(std::to_string(m_pPointsCp->GetAmount()));
	}

private:
	PointsCp* m_pPointsCp{};
	dae::UIPointsCp* m_pUIPointsCp{};
};