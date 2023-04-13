#include "Map.h"
#include "Character.h"

void Map::Initialize(const std::vector<Character>& character)
{
	mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));

	for (auto& i : character)
	{
		mGameMap[i.GetYPosition()][i.GetXPosition()] = i.GetCharacter();
	}
}

void Map::Draw() const
{
	for (const auto& row : mGameMap)
	{
		for (const auto& column : row)
		{
			std::cout << column;
		}
		std::cout << '\n';
	}
}

//This function updates the map with the players new position, and draws a map tile where
//The player was so it doesnt leave a trail of player characters.
void Map::Update(size_t oldX, size_t oldY, size_t newX, size_t newY, char character)
{
	mGameMap[oldY][oldX] = mMapTile; // Draw new map tile where player was
	mGameMap[newY][newX] = character; // Draw player at new position
}

size_t Map::GetMaxRows() const
{
	return mGameMap.size();
}

size_t Map::GetMaxColumns() const
{
    if (!mGameMap.empty()) 
    {
        return mGameMap[0].size();
    }
    else 
    {
        return 0;
    }
}

void Map::DrawRandomObjects(std::mt19937& mt, Tiles& tiles, int amountToPlace, Character& character)
{
    std::uniform_int_distribution<> rows{ 0, mMapRows - 1 };
    std::uniform_int_distribution<> columns{ 0, mMapColumns - 1 };

    for (int i{ }; i < amountToPlace; ++i)
    {
        int row = rows(mt);
        int col = columns(mt);

        // If the object is equal to a characters position, do not draw it, we don't want an object
        // to be drawn over characters.
        if ((row != character.GetXPosition() || col != character.GetYPosition()) &&
            (col != character.GetXPosition() || row != character.GetYPosition()))
        {
            // Store tile coordinates here so we can use them later
            mTileCoords.push_back(std::make_pair(row, col));

            mGameMap[row][col] = tiles.GetTile();
        }
    }
}

std::vector<std::pair<int, int>> Map::GetTileCoords()
{
	return mTileCoords;
}

void Map::DEBUG_DisplayTileCoords()
{
	for (const auto& coord : mTileCoords)
	{
		std::cout << "First: " << coord.first << ", Second: " << coord.second << std::endl;
	}
}

//Load a map from file
void Map::LoadFromFile()
{

}