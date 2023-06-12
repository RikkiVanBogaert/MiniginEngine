#include "GameObservers.h"

LivesObserver::LivesObserver(PlayerLivesCp* livesCp, UILivesCp* UILivesCp):
	m_pLivesCp(livesCp), m_pUILivesCp(UILivesCp)
{}

void LivesObserver::OnNotify(std::shared_ptr<ObserverEvent> event)
{
	if (!dynamic_cast<PlayerHitEvent*>(event.get())) return;

	m_pLivesCp->ChangeAmount(-1);
	m_pUILivesCp->SetValueText(std::to_string(m_pLivesCp->GetAmount()));
}

PointsObserver::PointsObserver(PointsCp* pointsCp, UIPointsCp* UIPointsCp) :
	m_pPointsCp(pointsCp), m_pUIPointsCp(UIPointsCp)
{}

void PointsObserver::OnNotify(std::shared_ptr<ObserverEvent> event)
{
	if (dynamic_cast<BlueTankKilledEvent*>(event.get()))
	{
		m_pPointsCp->ChangeAmount(100);
	}
	else if (dynamic_cast<RecognizerKilledEvent*>(event.get()))
	{
		m_pPointsCp->ChangeAmount(250);
	}
	m_pUIPointsCp->SetValueText(std::to_string(m_pPointsCp->GetAmount()));
}
