#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <utility>

#include "Tiles.h"

class Character;
class Map;

using IntPairVect = std::vector<std::pair<int, int>>;
using CharVect2D = std::vector<std::vector<char>>;

class Map
{
	public:
		Map(const std::string& mapName, int mapRows, int mapColumns, char mapTile) :
			mMapName(mapName), mMapRows(mapRows), mMapColumns(mapColumns), mMapTile(mapTile) {}

		void Initialize(const std::vector<Character>& character);

		void Draw() const;

		void Update(size_t oldX, size_t oldY, size_t newX, size_t newY, char character);

		size_t GetMaxRows() const;

		size_t GetMaxColumns() const;

		void DrawRandomObjects(Tiles& tiles, int amountToPlace, Character& character);

		IntPairVect GetTileCoords();

		void DEBUG_DisplayTileCoords();
		void DEBUG_GetTreatureCoords();

		void LoadFromFile();

		void PlaceRandomTreasure(Tiles& tiles, Character& character);

		size_t GetTreasureCoordsColumn() const;
		size_t GetTreasureCoordsRow() const;

	private:
		const std::string mMapName{ "Map Name" };
		int mMapRows{ 5 };
		int mMapColumns{ 5 };
		const char mMapTile{ ' ' };
		CharVect2D mGameMap;
		char mObject{ ' ' };
		IntPairVect mTileCoords;
		IntPairVect mTreasureCoords;
};

#endif