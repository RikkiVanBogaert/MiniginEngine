#include "GridCp.h"

GridCp::GridCp(dae::GameObject* owner):
ComponentBase(owner)
{}

void GridCp::AddCell(std::pair<std::string, const glm::vec2&> cell)
{
	m_Cells.insert(cell);
}
