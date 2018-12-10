//-------------------------------------------------------------------------------------
// Level.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------

#ifndef LEVEL_H
#define LEVEL_H

#include "Util.hpp"
#include "Enums.hpp"

// Constants for the game grid size.
static int const GRID_WIDTH = 19;
static int const GRID_HEIGHT = 19;

// The width and height of each tile in pixels.
static int const TILE_SIZE = 50;

// The level tile type.
struct Tile {
	TILE type;							// The type of tile this is.
	int columnIndex;					// The column index of the tile.
	int rowIndex;						// The row index of the tile.
	sf::Sprite sprite;					// The tile sprite.
	b2Body* physicsBody = nullptr;		// Physics body
	int H;								// Heuristic / movement cost to goal.
	int G;								// Movement cost. (Total of entire path)
	int F;								// Estimated cost for full path. (G + H)
	Tile* parentNode = nullptr;			// Node to reach this node.
};

class Level : public sf::Drawable {
public:
	/**
	* Default constructor.
	*/
	Level();

	/**
	* Constructor.
	* A renderWindow is needed in order for the level to calculate its position.
	* @param window The game window.
	*/
	Level(sf::RenderWindow& window);

	/**
	* Returns true if the given tile index is solid.
	* @param columnIndex The tile's column index.
	* @param rowIndex The tile's row index.
	* @return True if the given tile is solid.
	*/
	bool IsSolid(int columnIndex, int rowIndex);

	/**
	* Returns a to-pixel coordinate for spawning a game object
	* @param tile The tile that the game object will be spawned on top of
	* @return float vector of the position for spawning
	*/
	sf::Vector2f GetRandomSpawnLocationForTile(TILE tile);

	/**
	* Returns the screen position of the tile
	*/
	sf::Vector2f GetTilePosition(int columnIndex, int rowIndex);

	/**
	* Sets the index of a given tile in the 2D game grid.
	* This also changes the tile sprite, and is how tiles should be changed and set manually.
	* @param columnIndex The tile's column index.
	* @param rowIndex The tile's row index.
	* @param index The new index of the tile.
	*/
	void SetTile(int columnIndex, int rowIndex, TILE tileType);

	/**
	* Gets the index of the given tile.
	* @param columnIndex The column index of the tile to check.
	* @param rowIndex The row index of the tile to check.
	* @return The index of the given tile.
	*/
	TILE GetTileType(int columnIndex, int rowIndex) const;

	/**
	* Generate a random level.
	* return player starting position.
	*/
	sf::Vector2f GenerateLevel(b2World& world);

	/**
	* Gets the tile at the given position.
	* @param position The coordinates of the position to check.
	* @return A pointer to the tile at the given location.
	*/
	Tile* GetTile(sf::Vector2f position);

	/**
	* Gets the tile at the given position in the level array.
	* @param columnIndex The column that the tile is in.
	* @param rowIndex The row that the tile is in.
	* @return A pointer to the tile if valid.
	*/
	Tile* GetTile(int columnIndex, int rowIndex);

	/**
	* Checks if a given tile is valid.
	* @param columnIndex The column that the tile is in.
	* @param rowIndex The column that the row is in.
	* @return True if the tile is valid.
	*/
	bool TileIsValid(int columnIndex, int rowIndex);

	/**
	* Unlocks the door in the level.
	*/
	void UnlockDoor();

	/**
	* Return true if the given tile is a floor tile.
	* @param columnIndex The column that the tile is in.
	* @param rowIndex The column that the row is in.
	* @return True if the given tile is a floor tile.
	*/
	bool IsFloor(int columnIndex, int rowIndex);

	/**
	* Return true if the given tile is a floor tile.
	* @param tile The tile to check
	* @return True if the given tile is a floor tile.
	*/
	bool IsFloor(const Tile& tile);

	/**
	* Returns the size of the tiles in the level.
	* @return The size of the tiles in the level.
	*/
	int GetTileSize() const;

	/**
	* Adds a tile to the level.
	* These tiles are essentially sprites with a unique index. Once added, they can be loaded via the LoadLevelFromFile() function by including its index in the level data.
	* @param fileName The path to the sprite resource, relative to the project directory.
	* @param tileType The type of tile that is being added.
	* @return The index of the tile. This is used when building levels.
	*/
	int AddTile(std::string fileName, TILE tileType);

private:

	/**
	* Creates a path between two nodes in the recursive backtracker algorithm.
	*/
	void CreatePath(int columnIndex, int rowIndex);

	/**
	* Adds a given number of randomly sized rooms to the level to create some
	open space.
	*/
	void CreateRooms(int roomCount);

	/**
	* Calculates the correct texture for each tile in the level.
	*/
	void CalculateTextures(b2World& world);

	/**
	* Generates an entry and exit point for the given level.
	* return one tile above entry location.
	*/
	sf::Vector2f GenerateEntryExit();

	/**
	* Draws the level grid to the provided render window.
	* @param window The render window to draw the level to.
	* @param timeDelta The time that has elapsed since the last update.
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	* Checks if a given tile is a wall block.
	* @param columnIndex The column that the tile is in.
	* @param rowIndex The column that the row is in.
	* @return True if the given tile is a wall tile.
	*/
	bool IsWall(int columnIndex, int rowIndex);

private:
	/**
	* A 2D array that describes the level data.
	* The type is Tile, which holds a sprite and an index.
	*/
	Tile m_grid[GRID_WIDTH][GRID_HEIGHT];

	/**
	* The position of the level relative to the window.
	* This is to the top-left of the level grid.
	*/
	sf::Vector2i m_origin;

	/**
	* An array containing all texture IDs of the level tiles.
	*/
	int m_textureIDs[static_cast<int>(TILE::COUNT)];

	/**
	* The indices of the tile containing the levels door.
	*/
	sf::Vector2i m_doorTileIndices;
};
#endif