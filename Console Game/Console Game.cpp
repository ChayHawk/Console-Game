//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.0.11
// Version Date     : March 29th 2023 @ 11:10 AM
// Date Created     : 
// Lines of Code    : 220
// Description      : 
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <utility>

void DirectionalError();

//=========================================================================================================
// TODO
//
// Make a way for the DrawMap function to draw maps of different sizes so when the player transitions
// maps, it can redraw the map and the new transition point. 
//=========================================================================================================

class MapGenerator;

//Can promote to a character class when i learn virtual, then inherit from there.
class Player
{
public:
	Player(char player, int posX, int posY) : mPlayer(player), mPosX(posX), mPosY(posY) {}

	enum class Direction
	{
		UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
	};

	int GetPositionX() const
	{
		return mPosX;
	}

	int GetPositionY() const
	{
		return mPosY;
	}

	char GetPlayerCharacter() const
	{
		return mPlayer;
	}

	void Movement(Player::Direction choice, MapGenerator& mapGenerator);

private:
	const char mPlayer{ 'O' };
	int mPosX{ };
	int mPosY{ };
};



class MapGenerator
{
public:
	MapGenerator(const std::string& mapName, int mapRows, int mapColumns, char mapTile) :
		mMapName(mapName), mMapRows(mapRows), mMapColumns(mapColumns), mMapTile(mapTile) {}

	//Comment this out for now so we dont mess up the working code while testing
	/*void InitializeMap()
	{
		mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));
	}*/

	/*void DrawMap(int posX, int posY, char player)
	{
		for (int row{}; row < mMapRows; ++row)
		{
			for (int col{}; col < mMapColumns; ++col)
			{

				mGameMap[row][col] = mMapTile;
				mGameMap[posY][posX] = player;

				std::cout << mGameMap[row][col];
			}
			std::cout << '\n';
		}
	}*/


	void InitializeMap(const Player& player)
	{
		mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));
		mGameMap[player.GetPositionY()][player.GetPositionX()] = player.GetPlayerCharacter();
	}

	void DrawMap() const
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

	void Update(size_t oldX, size_t oldY, size_t newX, size_t newY, char player)
	{
		mGameMap[oldY][oldX] = mMapTile;
		mGameMap[newY][newX] = player;
	}

	int MaxRows() const
	{
		return mGameMap.size();
	}

	int MaxColumns() const
	{
		return !mGameMap.empty() ? mGameMap[0].size() : 0;
	}

private:
	const std::string mMapName{ "Map Name" };
	int mMapRows{ 5 };
	int mMapColumns{ 5 };
	const char mMapTile{ '+' };
	std::vector<std::vector<char>> mGameMap;
	char mTransitionTile{ 'H' };
};


int main()
{
	Player Hero('O', 7, 5);
	MapGenerator Field("Field", 20, 50, '-');

	Field.InitializeMap(Hero);

	while (true)
	{
		Field.DrawMap();

		std::cout << "X: " << Hero.GetPositionX() << " Y: " << Hero.GetPositionY() << "\n\n";

		std::cout << "What do you want to do?\n\n";

		std::cout << "1) Move Up\n";
		std::cout << "2) Move Down\n";
		std::cout << "3) Move Left\n";
		std::cout << "4) Move Right\n";

		int choice{ };

		std::cin >> choice;
		Hero.Movement(static_cast<Player::Direction>(choice), Field);
	}
}

void Player::Movement(Player::Direction choice, MapGenerator& mapGenerator) 
{
	switch (choice) 
	{
		case Direction::UP:
			if (mPosY) 
			{
				const auto oldY{ mPosY-- };

				mapGenerator.Update(mPosX, oldY, mPosX, mPosY, mPlayer);
				return;
			}
			break;

		case Direction::DOWN:
			if (mPosY < mapGenerator.MaxRows() - 1) 
			{
				const auto oldY{ mPosY++ };

				mapGenerator.Update(mPosX, oldY, mPosX, mPosY, mPlayer);
				return;
			}
			break;

		case Direction::LEFT:
			if (mPosX) 
			{
				const auto oldX{ mPosX-- };

				mapGenerator.Update(oldX, mPosY, mPosX, mPosY, mPlayer);
				return;
			}
			break;

		case Direction::RIGHT:
			if (mPosX < mapGenerator.MaxColumns() - 1) 
			{
				const auto oldX{ mPosX++ };

				mapGenerator.Update(oldX, mPosY, mPosX, mPosY, mPlayer);
				return;
			}
			break;

		default:
			std::cout << "Invalid Input\n";
			return;
	}

	DirectionalError();
}

void DirectionalError()
{
	std::cout << "Cannot go any further in this direction\n";
}