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

	void Update(float deltaTime) override;

	struct CellInfo
	{
		std::string type;
		glm::vec2 pos;
	};

	void AddCell(const CellInfo& cell);
	std::vector<CellInfo> GetCells() const { return m_Cells; }

	CellInfo GetCell(int index) const;
	int GetCellAtPos(const glm::vec2& pos) const;
	bool IsCellAtDirFree(int currCell, const glm::vec2& dir) const;
	int GetCellInDir(int currCell, const glm::vec2& dir) const;

	int m_GridRows{};
	int m_GridCols{};

private:
	std::vector<CellInfo> m_Cells{};

	const float m_CellSize;

};

