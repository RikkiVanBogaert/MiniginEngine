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
	LivesObserver(PlayerLivesCp* livesCp, UILivesCp* UILivesCp);

	virtual ~LivesObserver() override = default;

	LivesObserver(const LivesObserver& other) = delete;
	LivesObserver(LivesObserver&& other) = delete;
	LivesObserver& operator=(const LivesObserver& other) = delete;
	LivesObserver& operator=(LivesObserver&& other) = delete;

	void OnNotify(std::shared_ptr<ObserverEvent> event) override;

private:
	PlayerLivesCp* m_pLivesCp{};
	UILivesCp* m_pUILivesCp{};
};

class PointsObserver : public dae::Observer
{
public:
	PointsObserver(PointsCp* pointsCp, UIPointsCp* UIPointsCp);
	virtual ~PointsObserver() override = default;

	PointsObserver(const PointsObserver& other) = delete;
	PointsObserver(PointsObserver&& other) = delete;
	PointsObserver& operator=(const PointsObserver& other) = delete;
	PointsObserver& operator=(PointsObserver&& other) = delete;

	void OnNotify(std::shared_ptr<ObserverEvent> event) override;

private:
	PointsCp* m_pPointsCp{};
	UIPointsCp* m_pUIPointsCp{};
};