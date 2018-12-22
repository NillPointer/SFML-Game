#include "Components/AIComponent.hpp"
#include "Util.hpp"

AIComponent::AIComponent(GameObject& obj) : Component(obj), m_level(nullptr), m_target(nullptr), m_wanderPoint(INT_MIN, INT_MIN) {
}

void AIComponent::Update(float timeDelta) {
	if (!IsActive()) return;

	if (m_gameObject.GetPhysicsComponent() == nullptr || m_level == nullptr) return;
	auto size = PIXEL_PER_METER;
	if (m_gameObject.GetSpriteComponent() != nullptr && m_gameObject.GetSpriteComponent()->GetSprite()->getTexture() != nullptr) {
		auto textureSize = m_gameObject.GetSpriteComponent()->GetSprite()->getTexture()->getSize();
		size = textureSize.x > textureSize.y ? textureSize.x : textureSize.y;
	}
	if (m_wanderPoint.x == INT_MIN && m_wanderPoint.y == INT_MIN) m_wanderPoint = m_level->GetRandomSpawnLocation(false, false);
	if (Distance(m_gameObject.GetPhysicsComponent()->GetPosition(), m_wanderPoint) < size * 1.5) m_wanderPoint = m_level->GetRandomSpawnLocation(false, false);
	m_level->ResetNodes();

	UpdatePathFinding();

	if (m_path.size() == 0) return;

	Tile* target = m_path[0];
	sf::Vector2f position = m_level->GetTilePosition(target->columnIndex, target->rowIndex);
	sf::Vector2f direction = position - m_gameObject.GetPhysicsComponent()->GetPosition();
	m_gameObject.GetPhysicsComponent()->SetVelocity(Normalize(direction) * ENEMY_WALK_ACCELERATION);
}

void AIComponent::UpdatePathFinding() {
	Tile* startTile = m_level->GetTile(m_gameObject.GetPhysicsComponent()->GetPosition());
	Tile* endTile;

	if (m_target != nullptr && m_target->GetPhysicsComponent() != nullptr) {
		endTile = m_level->GetTile(m_target->GetPhysicsComponent()->GetPosition());
	} else {
		endTile = m_level->GetTile(m_wanderPoint);
	}

	std::vector<Tile*> openSet;
	std::set<Tile*> closedSet;

	openSet.push_back(startTile);
	
	while (openSet.size() > 0) {
		Tile* currentNode = openSet[0];

		for (int i = 0; i < openSet.size(); ++i) {
			if (openSet[i]->F < currentNode->F || openSet[i]->F == currentNode->F && openSet[i]->H < currentNode->H)
				currentNode = openSet[i];
		}

		std::vector<Tile*>::iterator it = std::find(openSet.begin(), openSet.end(), currentNode);
		int index = std::distance(openSet.begin(), it);
		openSet.erase(openSet.begin() + index);
		closedSet.insert(currentNode);

		if (currentNode == endTile) {
			RetracePath(startTile, endTile);
			return;
		}

		for (Tile* neighbour : m_level->GetNeighbours(currentNode)) {
			if (closedSet.find(neighbour) != closedSet.end()) continue;

			int newMovementCostToNeighbour = currentNode->G + GetDistance(currentNode, neighbour);
			if (newMovementCostToNeighbour < neighbour->G || !(std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end())) {
				neighbour->G = newMovementCostToNeighbour;
				neighbour->H = GetDistance(neighbour, endTile);
				neighbour->parentNode = currentNode;

				if (!(std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end())) openSet.push_back(neighbour);
			}
		}
	}
}

void AIComponent::RetracePath(Tile* startTile, Tile* targetTile) {
	Tile* currentTile = targetTile;
	m_path.clear();

	while (currentTile != startTile) {
		m_path.push_back(currentTile);
		currentTile = currentTile->parentNode;
	}

	std::reverse(m_path.begin(), m_path.end());
}

int AIComponent::GetDistance(Tile* tileA, Tile* tileB) {
	int distX = abs(tileA->columnIndex - tileB->columnIndex);
	int distY = abs(tileA->rowIndex - tileB->rowIndex);

	// srt(2) * 10 = 14
	if (distX > distY) return 14 * distY + 10 * (distX - distY);
	else 14 * distX + 10 * (distY - distX);
}

void AIComponent::SetLevel(Level* level) {
	m_level = level;
}

void AIComponent::SetTarget(std::shared_ptr<GameObject> target) {
	m_target = target;
}