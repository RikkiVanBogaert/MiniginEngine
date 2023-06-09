#include "GridCp.h"

GridCp::GridCp(dae::GameObject* owner):
ComponentBase(owner),
m_CellSize(8)
{}

void GridCp::Update(float)
{
	
}

void GridCp::AddCell(const CellInfo& cell)
{
	m_Cells.emplace_back(cell);
}


GridCp::CellInfo GridCp::GetCell(int index) const
{
	return m_Cells[index];
}

int GridCp::GetCellAtPos(const glm::vec2& pos) const 
{
	for(int i{}; i < m_Cells.size(); ++i)
	{
		if (m_Cells[i].pos == pos)
			return i;
	}

	return -1;
}

bool GridCp::IsCellAtDirFree(int , const glm::vec2& ) const
{
	/*const glm::vec2 nextCell{};
	for (int i{}; i < m_Cells.size(); ++i)
	{
		if (m_Cells[i].pos == pos)
			return i;
	}*/

	return true;
}

int GridCp::GetCellInDir(int currCell, const glm::vec2& dir) const
{
	int newCell{};
	if(dir.y < 0)
	{
		//going up
		newCell = currCell - m_GridCols;
	}
	else if (dir.y > 0)
	{
		//going down
		newCell = currCell + m_GridCols;
	}
	else if (dir.x < 0)
	{
		//going left
		newCell = currCell - 1;
	}
	else if (dir.x> 0)
	{
		//going right
		newCell = currCell + 1;
	}

	return newCell;
}
