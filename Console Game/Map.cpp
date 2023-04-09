#include "Map.h"

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

void Map::Update(size_t oldX, size_t oldY, size_t newX, size_t newY, char character)
{
	mGameMap[oldY][oldX] = mMapTile;
	mGameMap[newY][newX] = character;
}

size_t Map::GetMaxRows() const
{
	return mGameMap.size();
}

size_t Map::GetMaxColumns() const
{
	return !mGameMap.empty() ? mGameMap[0].size() : 0;
}

//Need to find a way to make this draw different amounts of each object. Could replace amountToPlace with a vector,
//Or make the tiles vector just a tile and place multiple of the function for each object.
void Map::DrawRandomObjects(std::mt19937& mt, const std::vector<Tiles>& tiles, int amountToPlace, Character& character)
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

            for (auto& j : tiles)
            {
                mGameMap[row][col] = j.GetTile();
            }
        }
    }
}

auto Map::GetTileCoords()
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