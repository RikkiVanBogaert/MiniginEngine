#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>

class Level final : public GameObject
{
public:
	Level(const std::string& mapFile);
	virtual ~Level() {};

private:
	std::vector<std::unique_ptr<TextureComponent>> m_TextureVec{};

	std::vector<int> parse_csv(const std::string& filename);
};

