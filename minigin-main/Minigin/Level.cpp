#include "Level.h"

using namespace std;
#include <fstream>
#include <sstream>

Level::Level(const std::string& mapFile)
{
	auto map = parse_csv(mapFile);

	//const int rows{54};
	const int cols{58};
	const float size{ 8 };
	const glm::vec2 startPos{100,10};
	glm::vec2 pos{startPos};
	for (int i{}; i < map.size(); ++i)
	{
		auto pBlock = std::make_unique<GameObject>();
		auto pTexture = std::make_shared<TextureComponent>(pBlock.get());
		switch (map[i])
		{
		case 0:
			pTexture->SetTexture("Resources/Level/wall.png");
			pBlock->SetTag("Wall");
			break;
		case 1:
			pTexture->SetTexture("Resources/Level/void.png");
			break;
		default:
			pTexture->SetTexture("Resources/Level/path.png");
			break;
		}
		pBlock->AddComponent(pTexture);
		
		pBlock->SetRelativePos({ pos.x, pos.y, 0 });
		pBlock->SetSize({size, size});
		AddChild(pBlock.get());
		m_pBlocks.push_back(std::move(pBlock));

		pos.x += size;

		if ((i + 1) % cols == 0)
		{
			pos.x = startPos.x;
			pos.y += size;
		}
	}
}

bool Level::CollisionHit(GameObject* object, const glm::vec3& dir)
{
	const auto objectPos = object->GetWorldTransform();

	//const std::vector<glm::vec2> cornerPoints = 
	//{ 
	//	{objectPos.x, objectPos.y}, //topLeft
	//	{objectPos.x , objectPos.y + object->GetSize().y / 2}, //bottomLeft
	//	{objectPos.x + object->GetSize().x / 2, objectPos.y}, //topRight
	//	{objectPos.x + object->GetSize().x / 2, objectPos.y + object->GetSize().y / 2} //bottomRight
	//};
	//const float rayLength = 1;
	//std::vector<glm::vec2> rayPoints{};
	//for (auto p : cornerPoints)
	//{
	//	rayPoints.push_back({p.x + dir.x * rayLength, p.y + dir.y * rayLength});
	//}

	const glm::vec2 midPoint = {objectPos.x + object->GetSize().x / 2, objectPos.y + object->GetSize().y / 2};
	const float rayLength = object->GetSize().x / 2;
	const glm::vec2 rayPoint = { midPoint.x + dir.x * rayLength, midPoint.y + dir.y * rayLength };

	for (const auto& wall : m_pBlocks)
	{
		if (wall->GetTag() != "Wall") continue;

		//possible improvement: not every corner needs to check every direction (bottomLeft doesnt need to check right/down, etc...
		/*for (auto r : rayPoints)
		{
			if (r.x > wall->GetWorldTransform().x && r.x < wall->GetWorldTransform().x + wall->GetSize().x &&
				r.y > wall->GetWorldTransform().y && r.y < wall->GetWorldTransform().y + wall->GetSize().y)
			{
				return false;
			}
		}*/

		if (rayPoint.x > wall->GetWorldTransform().x && rayPoint.x < wall->GetWorldTransform().x + wall->GetSize().x &&
			rayPoint.y > wall->GetWorldTransform().y && rayPoint.y < wall->GetWorldTransform().y + wall->GetSize().y)
		{
			return false;
		}
	}

	return true;
}


std::vector<int> Level::parse_csv(const std::string& filename)
{
	std::vector<int> result;

	// Open the file for reading
	std::ifstream file(filename);
	if (!file.is_open())
	{
		// Handle error
		std::cout << "Couldnt open file\n";
		return result;
	}

	// Read each line of the file
	std::string line;
	while (std::getline(file, line))
	{
		// Parse the line into integers
		std::stringstream ss(line);
		std::string field;
		while (std::getline(ss, field, ','))
		{
			try
			{
				result.push_back(std::stoi(field));
			}
			catch (std::invalid_argument&)
			{
				// Handle invalid data
				std::cout << "Invalid data in file\n";
			}
		}
	}

	std::cout << "File succesfully opened\n";
	return result;
}