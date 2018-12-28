#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

#include "GameObject.hpp"
#include "game-imap/IMap.h"
#include "Level.hpp"
#include "Components/Component.hpp"

class Component;

class AIComponent : public Component {
public:
	AIComponent(GameObject& obj);

	void Update(float timeDelta);

	void SetLevel(Level* level);

	void SetIMap(GameIMap::InfluenceMap* imap);

	void SetTarget(std::shared_ptr<GameObject> target);

private:
	void UpdatePathFinding();
	void RetracePath(Tile* startTile, Tile* targetTile);
	int GetDistance(Tile* tileA, Tile* tileB);

	Level* m_level;
	GameIMap::InfluenceMap* m_imap;
	sf::Vector2f m_wanderPoint;
	std::shared_ptr<GameObject> m_target;

	std::vector<Tile*> m_path;
};

#endif // !AICOMPONENT_HPP
