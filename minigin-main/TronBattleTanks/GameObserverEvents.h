#pragma once
#include "ObserverEvent.h"


class PlayerHit final : public ObserverEvent {};

class BlueTankKilled final : public ObserverEvent {};

class RecognizerKilled final : public ObserverEvent {};
