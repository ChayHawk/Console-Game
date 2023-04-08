#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>

#include "Tiles.h"
#include "Character.h"

class Character;
class Map;

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

		void DrawRandomObjects(std::mt19937& mt, const Tiles& tile, int amountToPlace, Character& character);

	private:
		const std::string mMapName{ "Map Name" };
		int mMapRows{ 5 };
		int mMapColumns{ 5 };
		const char mMapTile{ '+' };
		std::vector<std::vector<char>> mGameMap;
		char mTransitionTile{ 'H' };
		char mObject{ '#' };
};

#endif