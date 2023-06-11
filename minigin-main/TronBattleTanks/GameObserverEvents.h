#pragma once
#include "ObserverEvent.h"


class PlayerHitEvent final : public ObserverEvent
{};

class BlueTankKilledEvent final : public ObserverEvent
{};

class RecognizerKilledEvent final : public ObserverEvent
{};
