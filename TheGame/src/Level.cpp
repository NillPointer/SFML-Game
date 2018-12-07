#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Level.hpp"
#include "TextureManager.hpp"
#include "Util.hpp"

// Default constructor.
Level::Level() {}

// Constructor.
Level::Level(sf::RenderWindow& window) :
	m_origin({ 0, 0 }),
	m_floorNumber(1),
	m_roomNumber(0),
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

// Create and adds a tile sprite to the list of those available.
int Level::AddTile(std::string fileName, TILE tileType) {
	// Add the texture to the texture manager.
	int textureID = TextureManager::AddTexture(fileName);

	if (textureID < 0) {
		return -1; // Failed
	} else {
		m_textureIDs[static_cast<int>(tileType)] = textureID;
	}

	// Return the ID of the tile.
	return textureID;
}

// Checks if a given tile is passable
bool Level::IsSolid(int i, int j) {
	// Check that the tile is valid
	if (TileIsValid(i, j)) {
		int tileIndex = static_cast<int>(m_grid[i][j].type);
		return (((tileIndex != static_cast<int>(TILE::FLOOR)) && (tileIndex != static_cast<int>(TILE::FLOOR_ALT))) && (tileIndex != static_cast<int>(TILE::WALL_DOOR_UNLOCKED)));
	} else
		return false;
}

// Returns the position of the level relative to the application window.
sf::Vector2f Level::GetPosition() const {
	return sf::Vector2f(static_cast<float>(m_origin.x), static_cast<float>(m_origin.y));
}

// Returns the id of the given tile in the 2D level array.
TILE Level::GetTileType(int columnIndex, int rowIndex) const {
	// Check that the parameters are valid.
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT)) {
		return TILE::EMPTY; // failed
	}

	// Fetch the id.
	return m_grid[columnIndex][rowIndex].type;
}

// Sets the id of the given tile in the grid.
void Level::SetTile(int columnIndex, int rowIndex, TILE tileType) {
	// Check that the provided tile index is valid.
	if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT)) {
		return;
	}

	// check that the sprite index is valid
	if (tileType >= TILE::COUNT) {
		return;
	}

	// change that tiles sprite to the new index
	m_grid[columnIndex][rowIndex].type = tileType;
	m_grid[columnIndex][rowIndex].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(tileType)]));
}

// Gets the current floor number.
int Level::GetFloorNumber() const {
	return m_floorNumber;
}

// Gets the current room number.
int Level::GetRoomNumber() const {
	return m_roomNumber;
}

// Checks if a given tile is valid.
bool Level::TileIsValid(int column, int row) {
	bool validColumn, validRow;

	validColumn = ((column >= 0) && (column < GRID_WIDTH));
	validRow = ((row >= 0) && (row < GRID_HEIGHT));

	return (validColumn && validRow);
}

// Gets the size of the level in terms of tiles.
sf::Vector2i Level::GetSize() const {
	return sf::Vector2i(GRID_WIDTH, GRID_HEIGHT);
}

// Gets the tile that the position lies on.
Tile* Level::GetTile(sf::Vector2f position) {
	// Convert the position to relative to the level grid.
	position.x -= m_origin.x;
	position.y -= m_origin.y;

	// Convert to a tile position.
	int tileColumn, tileRow;

	tileColumn = static_cast<int>(position.x) / TILE_SIZE;
	tileRow = static_cast<int>(position.y) / TILE_SIZE;

	return &m_grid[tileColumn][tileRow];
}

// Returns a pointer to the tile at the given index.
Tile* Level::GetTile(int columnIndex, int rowIndex) {
	if (TileIsValid(columnIndex, rowIndex)) {
		return &m_grid[columnIndex][rowIndex];
	} else {
		return nullptr;
	}
}

// Loads a level from a .txt file.
bool Level::LoadLevelFromFile(std::string fileName, b2World& world) {
	// Create all the fields we need.
	std::ifstream file(fileName);

	// Read level data into 2D int array that describes the level.
	if (file.is_open()) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			for (int i = 0; i < GRID_WIDTH; ++i) {
				// Get the cell that we're working on.
				auto& cell = m_grid[i][j];

				// Read the character. Out of 4 characters we only want 2nd and 3rd.
				std::string input;

				file.get();
				input += file.get();
				input += file.get();
				file.get();

				// Convert string to int.
				std::stringstream convert(input);
				int tileID;
				convert >> tileID;

				// Set type, sprite and position.
				cell.type = static_cast<TILE>(tileID);
				cell.sprite.setTexture(TextureManager::GetTexture(m_textureIDs[tileID]));
				cell.sprite.setPosition(m_origin.x + (TILE_SIZE * i), m_origin.y + (TILE_SIZE * j));
/* TODO for testing purposes - remove later */ static char* t = "The door is closed";
				if (IsSolid(i, j)) {
					b2BodyDef bodyDef;
					bodyDef.type = b2_staticBody;
					auto posX = cell.sprite.getPosition().x + cell.sprite.getTexture()->getSize().x/2.0f;
					auto posY = cell.sprite.getPosition().y + cell.sprite.getTexture()->getSize().y / 2.0f;
					bodyDef.position.Set(posX / PIXEL_PER_METER, posY/ PIXEL_PER_METER);
					cell.physicsBody = world.CreateBody(&bodyDef);
/* TODO for testing purposes - remove later */ if (cell.type == TILE::WALL_DOOR_LOCKED) cell.physicsBody->SetUserData(&t);

					b2PolygonShape shape;
					b2FixtureDef fixture;
					shape.SetAsBox(0.8f, 0.8f);
					fixture.shape = &shape;
					fixture.friction = 0.0f;
					cell.physicsBody->CreateFixture(&fixture);
				}

				// Check for entry/exit nodes.
				if (cell.type == TILE::WALL_DOOR_LOCKED) {
					// Save the location of the exit door.
					m_doorTileIndices = sf::Vector2i(i, 0);
				}
			}

			// Read end line char.
			file.get();
		}

		file.close(); //closing the file
	} else {
		return false;
	}

	return true;
}

// Generate a random level.
sf::Vector2f Level::GenerateLevel(b2World& world) {
	for (int i = 0; i < GRID_WIDTH; ++i) {
		for (int j = 0; j < GRID_HEIGHT; ++j) {
			if ((i % 2 != 0) && (j % 2 != 0)) {
				m_grid[i][j].type = TILE::EMPTY;
			} else {
				m_grid[i][j].type = TILE::WALL_TOP;
				m_grid[i][j].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::WALL_TOP)]));
			}

			m_grid[i][j].sprite.setPosition(m_origin.x + (TILE_SIZE * i), m_origin.y + (TILE_SIZE * j));
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
/* TODO for testing purposes - remove later */ static char* t = "The door is closed";

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
	m_grid[endI][0].physicsBody->SetUserData(&t);
	return{(((float)startI + 0.5f) * TILE_SIZE) + m_origin.x, ((GRID_HEIGHT - 1.5f) * TILE_SIZE) + (float)m_origin.y };
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
				m_grid[i][j].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[value]));

				b2BodyDef bodyDef;
				bodyDef.type = b2_staticBody;
				auto posX = m_grid[i][j].sprite.getPosition().x + m_grid[i][j].sprite.getTexture()->getSize().x / 2.0f;
				auto posY = m_grid[i][j].sprite.getPosition().y + m_grid[i][j].sprite.getTexture()->getSize().y / 2.0f;
				bodyDef.position.Set(posX / PIXEL_PER_METER, posY / PIXEL_PER_METER);
				m_grid[i][j].physicsBody = world.CreateBody(&bodyDef);

				b2PolygonShape shape;
				b2FixtureDef fixture;
				shape.SetAsBox(0.8f, 0.8f);
				fixture.shape = &shape;
				fixture.friction = 0.0f;
				m_grid[i][j].physicsBody->CreateFixture(&fixture);
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
				// Mark the tile as floor.
				tile->type = TILE::FLOOR;
				tile->sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

				// Knock that wall down.
				int ddx = currentTile->columnIndex + (directions[i].x / 2);
				int ddy = currentTile->rowIndex + (directions[i].y / 2);
				Tile* wall = &m_grid[ddx][ddy];
				wall->type = TILE::FLOOR;
				wall->sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

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
						m_grid[newI][newY].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));
					}
				}
			}
		}
	}
}

// Checks if a given tile is a wall block.
bool Level::IsWall(int i, int j) {
	if (TileIsValid(i, j))
		return m_grid[i][j].type <= TILE::WALL_INTERSECTION;
	else
		return false;
}

// Unlocks the door in the level.
void Level::UnlockDoor() {
	SetTile(m_doorTileIndices.x, m_doorTileIndices.y, TILE::WALL_DOOR_UNLOCKED);
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(int columnIndex, int rowIndex) {
	Tile* tile = &m_grid[columnIndex][rowIndex];

	return ((tile->type == TILE::FLOOR) || (tile->type == TILE::FLOOR_ALT));
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(const Tile& tile) {
	return ((tile.type == TILE::FLOOR) || (tile.type == TILE::FLOOR_ALT));
}

// Gets the size of the tiles in the level.
int Level::GetTileSize() const {
	return TILE_SIZE;
}

// Draws the level grid to the given render window.
void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Draw the level tiles.
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			target.draw(m_grid[i][j].sprite);
		}
	}
}