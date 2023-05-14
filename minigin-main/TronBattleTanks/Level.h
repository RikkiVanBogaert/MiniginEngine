#pragma once
#include "GameObject.h"
#include "TextureComponent.h"
#include <vector>
#include <memory>


class Level final : public dae::GameObject
{
public:
	Level(const std::vector<int>& map, dae::Scene* scene);
	//virtual ~Level() = default;

	virtual void Update(float deltaTime) override;

	bool CollisionHit(GameObject* object, const glm::vec2& dir);
	bool HitWall(const glm::vec2& start, const glm::vec2& end);

	glm::vec2 GetRandomSpawnPos() const;

	void OnLevelLoad();
	void OnLevelDestroy();

private:
	std::vector<std::shared_ptr<GameObject>> m_pLevelObjects{};
	std::vector<GameObject*> m_pWalls;
	std::vector<GameObject*> m_pPaths;
	std::vector<GameObject*> m_pTeleport;

	std::vector<glm::vec2> m_SpawnPosPlayers{};
	std::vector<glm::vec2> m_SpawnPosBlueTanks{};

	void CreateMap(const std::vector<int>& map, int columns);

	void UpdateBullets();
	bool CheckTeleportCollision(const glm::vec2& rayPoint);

	void LoadSinglePlayer() const;
	void LoadCoop() const;
	void LoadVersus() const;


    struct Square
	{
        float x; // x coordinate of square center
        float y; // y coordinate of square center
        float size; // size of square (assumed to be the same for width and height)
    };

    bool isSquareInWay(const Square& s1, const Square& s2, const Square& obstacle) {
        // Calculate the distance between the centers of the two squares
        double distance = std::sqrt(std::pow(s2.x - s1.x, 2) + std::pow(s2.y - s1.y, 2));

        // Calculate the minimum distance between the centers of the two squares required to avoid collision
        double minDistance = (s1.size + s2.size) / 2.0;

        // If the distance between the centers is less than the minimum required distance, the squares are colliding
        if (distance < minDistance) {
            // Calculate the distance between the center of the obstacle square and the line segment defined by the centers of the two squares
            double segmentLength = std::sqrt
        	(std::pow(s2.x - s1.x, 2) + std::pow(s2.y - s1.y, 2));
            double projection = ((obstacle.x - s1.x) * (s2.x - s1.x) + (obstacle.y - s1.y) * (s2.y - s1.y)) / std::pow(segmentLength, 2);
            double closestX = s1.x + projection * (s2.x - s1.x);
            double closestY = s1.y + projection * (s2.y - s1.y);
            double distanceToSegment = std::sqrt(std::pow(obstacle.x - closestX, 2) + std::pow(obstacle.y - closestY, 2));

            // If the distance between the obstacle square and the line segment is less than the size of the obstacle square, there is a collision
            if (distanceToSegment < obstacle.size / 2.0) {
                return true;
            }
        }

        // If there is no collision, return false
        return false;
    }

};

