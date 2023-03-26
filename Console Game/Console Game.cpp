//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.7
// Version Date     : March 25th 2023 @ 9:21 AM
// Date Created     : 
// Lines of Code    : 230
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

class Player;

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
				//How to transition from one map to another?
				//One way could be by using std::map to store the map and the
				//map ID
				if (player == mTransitionTile)
				{
					//How to get last map transitioned to?
				}
				else
				{
					mGameMap[row][col] = mMapTile;
				}
				mGameMap[playerY][playerX] = player;

				std::cout << mGameMap[row][col];
			}
			std::cout << '\n';
		}
	}

	//TODO: Generate random Map ID or let user set it
	void AddLevel(MapGenerator mapGenerator)
	{
		mLevels.insert(std::pair<MapGenerator, int>(mapGenerator, mMapID));
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
	std::map<MapGenerator, int> mLevels;
	char mTransitionTile{ 'H' };
	int mMapID{ 0 };
};



//Can promote to a character class when i learn virtual, then inherit from there.
class Player
{
public:
	Player(char player, int posX, int posY) : mPlayer(player), mPosX(posX), mPosY(posY) {}

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

	void Movement(int choice, MapGenerator);

private:
	const char mPlayer{ 'O' };
	int mPosX{ };
	int mPosY{ };
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
		Hero.Movement(choice, Courtyard);
	}
}

void Player::Movement(int choice, MapGenerator mapGenerator)
{
	enum class Direction
	{
		UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
	};

	switch (choice)
	{
	case static_cast<int>(Direction::UP):
		if (mPosY)
		{
			--mPosY;
			return;
		}
		break;

	case static_cast<int>(Direction::DOWN):
		if (mPosY < mapGenerator.MaxRows() - 1)
		{
			++mPosY;
			return;
		}
		break;

	case static_cast<int>(Direction::LEFT):
		if (mPosX)
		{
			--mPosX;
			return;
		}
		break;

	case static_cast<int>(Direction::RIGHT):
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