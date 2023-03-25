//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.5
// Version Date     : March 25th 2023 @ 11:41 AM
// Date Created     : 
// Lines of Code    : 256
// Description      : 
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <utility>

void DirectionalError();

//TODO: Add map transitioning to Map class. Map transitions should be
//handled internally, so its not something that should be exposed to the user.
//One way this could be done is an std::map or vector could be created to 
//hold the levels, then when the player hits a transition spot it could call the
//new map and draw it.

class Map
{
public:
	Map(const std::string& mapName, int mapRows, int mapColumns, char mapTile) :
		mMapName(mapName), mMapRows(mapRows), mMapColumns(mapColumns), mMapTile(mapTile) {}

	//Comment this out for now so we dont mess up the working code while testing
	//void InitializeMap() 
	//{
	//	mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));
	//}

	//void DrawMap(int posX, int posY, char player, char transition)
	//{
	//	for (int row{}; row < mMapRows; ++row) 
	//	{
	//		for (int col{}; col < mMapColumns; ++col)
	//		{
	//			if (posX == transition && posY == transition)
	//			{
	//				/*mGameMap[row][col] = mMapTile;
	//				mGameMap[posY][posX] = player;

	//				std::cout << mGameMap[row][col];*/
	//			}
	//			else
	//			{
	//				mGameMap[row][col] = mMapTile;
	//				mGameMap[posY][posX] = player;

	//				std::cout << mGameMap[row][col];
	//			}
	//			
	//		}
	//		std::cout << '\n';
	//	}
	//}

	void InitializeMap()
	{
		mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));
	}

	void DrawMap(int posX, int posY, char player, char transition)
	{
		for (int row{}; row < mMapRows; ++row)
		{
			for (int col{}; col < mMapColumns; ++col)
			{
				if (posX == transition && posY == transition)
				{
					/*mGameMap[row][col] = mMapTile;
					mGameMap[posY][posX] = player;

					std::cout << mGameMap[row][col];*/
				}
				else
				{
					mGameMap[row][col] = mMapTile;
					mGameMap[posY][posX] = player;

					std::cout << mGameMap[row][col];
				}

			}
			std::cout << '\n';
		}
	}

	int MaxRow() const
	{
		return mGameMap.size();
	}

	int MaxCol() const
	{
		return !mGameMap.empty() ? mGameMap[0].size() : 0;
	}

	int GetTransitionX() const
	{
		return mTransitionX;
	}

	int GetTransitionY() const
	{
		return mTransitionY;
	}

	void AddMap(const Map& map, int mapID)
	{
		mapList.insert(std::pair<Map, int>(map, mapID));
	}

private:
	const std::string mMapName{ "Map Name" };
	int mMapRows{ 5 };
	int mMapColumns{ 5 };
	const char mMapTile{ '+' };
	std::vector<std::vector<char>> mGameMap;
	std::map<Map, int> mapList;
	int mTransitionX{ 0 };
	int mTransitionY{ 0 };
	char mTransitionCharacter{ 'Z' };
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

	char GetPlayer() const
	{
		return mPlayer;
	}

	void Movement(int choice, Map);

private:
	const char mPlayer{ 'O' };
	int mPosX{ };
	int mPosY{ };
};

int main()
{
	Player Hero('O', 7, 5);
	Map Courtyard("Courtyard", 10, 20, '-');
	Map Field("Field", 20, 50, '-');

	Courtyard.InitializeMap();
	Field.InitializeMap();

	while (true)
	{
		//Map transition code, need to figure out how to put this in member functions
		if (Hero.GetPositionX() == 7 && Hero.GetPositionY() == 5)
		{
			Field.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayer());
		}
		else if (Hero.GetPositionX() == 7 && Hero.GetPositionY() == 6)
		{
			Courtyard.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayer());
		}
		else
		{
			Courtyard.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayer());
		}

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

void Player::Movement(int choice, Map map)
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
		if (mPosY < map.MaxRow() - 1)
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
		if (mPosX < map.MaxCol() - 1)
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

