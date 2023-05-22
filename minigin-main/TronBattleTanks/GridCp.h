#pragma once
#include <map>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"

class GridCp final : public dae::ComponentBase
{
public:
	GridCp(dae::GameObject* owner);

	void AddCell(std::pair<std::string, const glm::vec2&> cell);
	std::map<std::string, glm::vec2> GetCells() const { return m_Cells; }

private:
	std::map<std::string, glm::vec2> m_Cells;
};

