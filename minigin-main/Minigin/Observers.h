#pragma once
#include "ObserverEvent.h"
#include <string>

#include "../TronBattleTanks/DerCounterCps.h"
#include "../TronBattleTanks/UICp.h"

class LivesCp;

namespace dae
{
	class UILivesCp;
	// Forward declaration of the Subject class
	class Subject;

	// Observer interface
	class Observer
	{
	public:
		virtual void Update(ObserverEvent event) = 0;
	};

	// Concrete observer classes
	class LivesObserver : public Observer
	{
	public:
		LivesObserver(LivesCp* livesCp, UILivesCp* UILivesCp):
		m_pLivesCp(livesCp), m_pUILivesCp(UILivesCp)
		{}
		void Update(ObserverEvent event) override
		{
			//m_pLivesCp->ChangeAmount(-1);
			if (event != PlayerHit) return;

			m_pUILivesCp->SetValueText(std::to_string(m_pLivesCp->GetAmount()));
		}

	private:
		LivesCp* m_pLivesCp{};
		UILivesCp* m_pUILivesCp{};
	};

	class PointsObserver : public Observer
	{
	public:
		PointsObserver(PointsCp* livesCp, UIPointsCp* UILivesCp) :
			m_pPointsCp(livesCp), m_pUIPointsCp(UILivesCp)
		{}
		void Update(ObserverEvent event) override
		{
			if(event == BlueTankKilled)
			{
				m_pPointsCp->ChangeAmount(100);
			}
			else if(event == RecognizerKilled)
			{
				m_pPointsCp->ChangeAmount(250);
			}
			m_pUIPointsCp->SetValueText(std::to_string(m_pPointsCp->GetAmount()));
		}

	private:
		PointsCp* m_pPointsCp{};
		UIPointsCp* m_pUIPointsCp{};
	};


}
