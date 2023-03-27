//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.9
// Version Date     : March 25th 2023 @ 11:51 AM
// Date Created     : 
// Lines of Code    : 217
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


	void InitializeMap()
	{
		mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));
	}

	void DrawMap(int playerX, int playerY, char player)
	{
		for (int row{}; row < mMapRows; ++row)
		{
			for (int col{}; col < mMapColumns; ++col)
			{
				mGameMap[row][col] = mMapTile;
				mGameMap[playerY][playerX] = player;

				std::cout << mGameMap[row][col];
			}
			std::cout << '\n';
		}
	}

	//Look on CPP forum for solution
	void UpdateMap()
	{

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
	MapGenerator Courtyard("Courtyard", 10, 20, '-');
	MapGenerator Field("Field", 20, 50, '-');

	Courtyard.InitializeMap();
	Field.InitializeMap();

	while (true)
	{
		Courtyard.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayerCharacter());

		std::cout << "X: " << Hero.GetPositionX() << " Y: " << Hero.GetPositionY() << "\n\n";

		std::cout << "What do you want to do?\n\n";

		std::cout << "1) Move Up\n";
		std::cout << "2) Move Down\n";
		std::cout << "3) Move Left\n";
		std::cout << "4) Move Right\n";

		int choice{ };

		std::cin >> choice;
		Hero.Movement(static_cast<Player::Direction>(choice), Courtyard);
	}
}

void Player::Movement(Player::Direction choice, MapGenerator& mapGenerator)
{
	switch (choice)
	{
	case Direction::UP:
		if (mPosY)
		{
			--mPosY;
			return;
		}
		break;

	case Direction::DOWN:
		if (mPosY < mapGenerator.MaxRows() - 1)
		{
			++mPosY;
			return;
		}
		break;

	case Direction::LEFT:
		if (mPosX)
		{
			--mPosX;
			return;
		}
		break;

	case Direction::RIGHT:
		if (mPosX < mapGenerator.MaxColumns() - 1)
		{
			++mPosX;
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