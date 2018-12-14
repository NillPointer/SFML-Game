#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Level.hpp"
#include "AssetManager.hpp"
#include "Util.hpp"

// Default constructor.
Level::Level() {}

// Constructor.
Level::Level(sf::RenderWindow& window) :
	m_origin({ 0, 0 }),
	m_doorTileIndices({ 0, 0 }) {
	// Load all tiles.
	AddTile("resource/tiles/spr_tile_floor.png", TILE::FLOOR);

	AddTile("resource/tiles/spr_tile_wall_top.png", TILE::WALL_TOP);
	AddTile("resource/tiles/spr_tile_wall_top_left.png", TILE::WALL_TOP_LEFT);
	AddTile("resource/tiles/spr_tile_wall_top_right.png", TILE::WALL_TOP_RIGHT);
	AddTile("resource/tiles/spr_tile_wall_top_t.png", TILE::WALL_TOP_T);
	AddTile("resource/tiles/spr_tile_wall_top_end.png", TILE::WALL_TOP_END);

	AddTile("resource/tiles/spr_tile_wall_bottom_left.png", TILE::WALL_BOTTOM_LEFT);
	AddTile("resource/tiles/spr_tile_wall_bottom_right.png", TILE::WALL_BOTTOM_RIGHT);
	AddTile("resource/tiles/spr_tile_wall_bottom_t.png", TILE::WALL_BOTTOM_T);
	AddTile("resource/tiles/spr_tile_wall_bottom_end.png", TILE::WALL_BOTTOM_END);

	AddTile("resource/tiles/spr_tile_wall_side.png", TILE::WALL_SIDE);
	AddTile("resource/tiles/spr_tile_wall_side_left_t.png", TILE::WALL_SIDE_LEFT_T);
	AddTile("resource/tiles/spr_tile_wall_side_left_end.png", TILE::WALL_SIDE_LEFT_END);
	AddTile("resource/tiles/spr_tile_wall_side_right_t.png", TILE::WALL_SIDE_RIGHT_T);
	AddTile("resource/tiles/spr_tile_wall_side_right_end.png", TILE::WALL_SIDE_RIGHT_END);

	AddTile("resource/tiles/spr_tile_wall_intersection.png", TILE::WALL_INTERSECTION);
	AddTile("resource/tiles/spr_tile_wall_single.png", TILE::WALL_SINGLE);

	AddTile("resource/tiles/spr_tile_wall_entrance.png", TILE::WALL_ENTRANCE);
	AddTile("resource/tiles/spr_tile_door_locked.png", TILE::WALL_DOOR_LOCKED);
	AddTile("resource/tiles/spr_tile_door_unlocked.png", TILE::WALL_DOOR_UNLOCKED);

	// Calculate the top left of the grid.
	m_origin.x = (window.getSize().x - (GRID_WIDTH * TILE_SIZE));
	m_origin.x /= 2;

	m_origin.y = (window.getSize().y - (GRID_HEIGHT * TILE_SIZE));
	m_origin.y /= 2;

	// Store the column and row information for each node.
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			auto cell = &m_grid[i][j];
			cell->columnIndex = i;
			cell->rowIndex = j;
		}
	}
}

int Level::AddTile(std::string fileName, TILE tileType) {
	int textureID = AssetManager::AddTexture(fileName);
	if (textureID < 0) return -1; // Failed
	else m_textureIDs[static_cast<int>(tileType)] = textureID;
	return textureID;
}

bool Level::IsSolid(int i, int j) {
	if (TileIsValid(i, j)) {
		int tileIndex = static_cast<int>(m_grid[i][j].type);
		return (((tileIndex != static_cast<int>(TILE::FLOOR)) && (tileIndex != static_cast<int>(TILE::FLOOR_ALT))) && (tileIndex != static_cast<int>(TILE::WALL_DOOR_UNLOCKED)));
	} else return false;
}

TILE Level::GetTileType(int columnIndex, int rowIndex) const {
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT)) return TILE::EMPTY;
	return m_grid[columnIndex][rowIndex].type;
}

void Level::SetTile(int columnIndex, int rowIndex, TILE tileType) {
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT)) return;
	if (tileType >= TILE::COUNT) return;

	m_grid[columnIndex][rowIndex].type = tileType;
	m_grid[columnIndex][rowIndex].sprite.setTexture(AssetManager::GetTexture(m_textureIDs[static_cast<int>(tileType)]));
}

bool Level::TileIsValid(int column, int row) {
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < GRID_WIDTH));
	validRow = ((row >= 0) && (row < GRID_HEIGHT));

	return (validColumn && validRow);
}

std::vector<Tile*> Level::GetNeighbours(Tile* tile) {
	std::vector<Tile*> neighbours;

	for (int x = -1; x <= 1; ++x) {
		for (int y = -1; y <= 1; ++y) {
			if (pow(x,2) == pow(y,2)) continue;
			int checkX = tile->columnIndex + x;
			int checkY = tile->rowIndex + y;

			if (TileIsValid(checkX, checkY) && IsFloor(checkX, checkY)) neighbours.push_back(GetTile(checkX, checkY));
		}
	}
	return neighbours;
}

// Resets the A* data of all tiles.
void Level::ResetNodes() {
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			m_grid[i][j].parentNode = nullptr;
			m_grid[i][j].H = 0;
			m_grid[i][j].G = 0;
			m_grid[i][j].F = 0;
		}
	}
}

// Gets the tile that the position lies on.
Tile* Level::GetTile(sf::Vector2f position) {
	position.x -= m_origin.x;
	position.y -= m_origin.y;

	int tileColumn, tileRow;

	tileColumn = static_cast<int>(position.x) / TILE_SIZE;
	tileRow = static_cast<int>(position.y) / TILE_SIZE;

	return &m_grid[tileColumn][tileRow];
}

Tile* Level::GetTile(int columnIndex, int rowIndex) {
	if (TileIsValid(columnIndex, rowIndex)) return &m_grid[columnIndex][rowIndex];
	else return nullptr;
}

sf::Vector2f Level::GetRandomSpawnLocation(bool wall, bool unique) {
	int columnIndex(0), rowIndex(0);
	bool usedPosition = true;

	while ((IsFloor(columnIndex, rowIndex) == wall) || usedPosition) {
		columnIndex = std::rand() % GRID_WIDTH;
		rowIndex = std::rand() % GRID_HEIGHT;
		usedPosition = unique ? m_spawnPositions.find(std::pair<int, int>(columnIndex, rowIndex)) != m_spawnPositions.end() : false;
	}

	m_spawnPositions.insert(std::pair<int, int>(columnIndex, rowIndex));

	return GetTilePosition(columnIndex, rowIndex);
}

sf::Vector2f Level::GetTilePosition(int columnIndex, int rowIndex) {
	sf::Vector2f position;
	position.x = m_origin.x + (columnIndex * TILE_SIZE) + (TILE_SIZE / 2);
	position.y = m_origin.y + (rowIndex * TILE_SIZE) + (TILE_SIZE / 2);
	return position;
}

sf::Vector2f Level::GenerateLevel(b2World& world) {

	m_spawnPositions.clear();

	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			if ((i % 2 != 0) && (j % 2 != 0)) {
				m_grid[i][j].type = TILE::EMPTY;
			} else {
				m_grid[i][j].type = TILE::WALL_TOP;
				m_grid[i][j].sprite.setTexture(AssetManager::GetTexture(m_textureIDs[static_cast<int>(TILE::WALL_TOP)]));
			}
			m_grid[i][j].sprite.setPosition(m_origin.x + (TILE_SIZE * i), m_origin.y + (TILE_SIZE * j));
			
			// Clear any previous physics bodies
			if (m_grid[i][j].physicsBody != nullptr) {
				world.DestroyBody(m_grid[i][j].physicsBody);
				m_grid[i][j].physicsBody = nullptr;
			}
		}
	}
	CreatePath(1, 1);
	CreateRooms(10);
	CalculateTextures(world);
	return GenerateEntryExit();
}

// Generates an entry and exit point for the given level.
sf::Vector2f Level::GenerateEntryExit() {
	int startI, endI;
	startI = endI = -1;

	while (startI == -1) {
		int index = std::rand() % GRID_WIDTH;
		if (m_grid[index][GRID_HEIGHT - 1].type == TILE::WALL_TOP) startI = index;
	}
	while (endI == -1) {
		int index = std::rand() % GRID_HEIGHT;
		if (m_grid[index][0].type == TILE::WALL_TOP) endI = index;
	}

	SetTile(startI, GRID_HEIGHT - 1, TILE::WALL_ENTRANCE);
	SetTile(endI, 0, TILE::WALL_DOOR_LOCKED);
	m_doorTileIndices = { endI, 0 };
	m_spawnPositions.insert(std::pair<int, int>(startI, GRID_HEIGHT - 2));
	return GetTilePosition(startI, GRID_HEIGHT - 2);
}

// Calculates the correct texture for each tile in the level.
void Level::CalculateTextures(b2World& world) {
	// For each tile in the grid.
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			// Check that the tile is a wall block.
			if (IsWall(i, j)) {
				int value = 0;
				TILE type = m_grid[i][j].type;
				if (IsWall(i, j - 1)) value += 1;
				if (IsWall(i + 1, j)) value += 2;
				if (IsWall(i, j + 1)) value += 4;
				if (IsWall(i - 1, j)) value += 8;
				m_grid[i][j].type = static_cast<TILE>(value);
				m_grid[i][j].sprite.setTexture(AssetManager::GetTexture(m_textureIDs[value]));

				auto posX = m_grid[i][j].sprite.getPosition().x + m_grid[i][j].sprite.getTexture()->getSize().x / 2.0f;
				auto posY = m_grid[i][j].sprite.getPosition().y + m_grid[i][j].sprite.getTexture()->getSize().y / 2.0f;
				m_grid[i][j].physicsBody = CreateSquarePhysicsBody(world, { posX, posY }, {0.77f, 0.77f});
				SetPhysicsBodyFilter(m_grid[i][j].physicsBody, WALL);
			}
		}
	}
}

// Create a path between two tiles in the level grid.
void Level::CreatePath(int columnIndex, int rowIndex) {
	Tile* currentTile = &m_grid[columnIndex][rowIndex];

	// Create a list of possible directions and sort randomly.
	sf::Vector2i directions[] = { { 0, -2 },{ 2, 0 },{ 0, 2 },{ -2, 0 } };
	std::random_shuffle(std::begin(directions), std::end(directions));

	// For each direction.
	for (int i = 0; i < 4; ++i) {
		// Get the new tile position.
		int dx = currentTile->columnIndex + directions[i].x;
		int dy = currentTile->rowIndex + directions[i].y;

		// If the tile is valid.
		if (TileIsValid(dx, dy)) {
			// Store the tile.
			Tile* tile = &m_grid[dx][dy];

			// If the tile has not yet been visited.
			if (tile->type == TILE::EMPTY) {
				// Mark the tile as wall.
				tile->type = TILE::FLOOR;
				tile->sprite.setTexture(AssetManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

				// Knock that wall down.
				int ddx = currentTile->columnIndex + (directions[i].x / 2);
				int ddy = currentTile->rowIndex + (directions[i].y / 2);
				Tile* wall = &m_grid[ddx][ddy];
				wall->type = TILE::FLOOR;
				wall->sprite.setTexture(AssetManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

				// Recursively call the function with the new tile.
				CreatePath(dx, dy);
			}
		}
	}
}

// Adds a given number of randomly sized rooms to the level to create some open space.
void Level::CreateRooms(int roomCount) {
	for (int i = 0; i < roomCount; ++i) {
		// Generate a room size.
		int roomWidth = std::rand() % 2 + 1;
		int roomHeight = std::rand() % 2 + 1;

		// Choose a random starting location.
		int startI = std::rand() % (GRID_WIDTH - 2) + 1;
		int startY = std::rand() % (GRID_HEIGHT - 2) + 1;

		for (int j = -1; j < roomWidth; ++j) {
			for (int z = -1; z < roomHeight; ++z) {
				int newI = startI + j;
				int newY = startY + z;

				// Check if the tile is valid.
				if (TileIsValid(newI, newY)) {
					// Check if the tile is not on an outer wall.
					if ((newI != 0) && (newI != (GRID_WIDTH - 1)) && (newY != 0) && (newY != (GRID_HEIGHT - 1))) {
						m_grid[newI][newY].type = TILE::FLOOR;
						m_grid[newI][newY].sprite.setTexture(AssetManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));
					}
				}
			}
		}
	}
}

bool Level::IsWall(int i, int j) {
	if (TileIsValid(i, j)) return m_grid[i][j].type <= TILE::WALL_INTERSECTION;
	else return false;
}

void Level::UnlockDoor() {
	b2Filter filter = m_grid[m_doorTileIndices.x][m_doorTileIndices.y].physicsBody->GetFixtureList()->GetFilterData();
	filter.categoryBits = UNLOCKED_DOOR;
	m_grid[m_doorTileIndices.x][m_doorTileIndices.y].physicsBody->GetFixtureList()->SetFilterData(filter);
	SetTile(m_doorTileIndices.x, m_doorTileIndices.y, TILE::WALL_DOOR_UNLOCKED);
}

bool Level::IsFloor(int columnIndex, int rowIndex) {
	Tile* tile = &m_grid[columnIndex][rowIndex];
	return ((tile->type == TILE::FLOOR) || (tile->type == TILE::FLOOR_ALT));
}

bool Level::IsFloor(const Tile& tile) {
	return ((tile.type == TILE::FLOOR) || (tile.type == TILE::FLOOR_ALT));
}

int Level::GetTileSize() const {
	return TILE_SIZE;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Draw the level tiles.
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			target.draw(m_grid[i][j].sprite);
		}
	}
}