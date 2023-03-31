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
#include <chrono>
#include <utility>

void DirectionalError();

class MapGenerator;

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
		//std::cout << "old x: " << oldX << " - old Y:" << oldY << '\n';
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

	//NOT WORKING
	//The reason this is not working is because the randomRows and randomColumns variables are the exact same
	//for all x amount of time the for loop loops, its not randomizing the positions each time.
	// 
	//BUGS
	//Sometimes vector goes out of range
	void DrawObjects(int randomRows, int randomColumns, char object, int amountToPlace, const Player& player)
	{
		//Test to see if we already have an object where we are going to draw one on the map.
		bool isPlaced{ false };

		std::cout << "randomRows: " << randomRows << " randomColumns: " << randomColumns << '\n';
		mGameMap[randomRows][randomColumns] = object;

		//for (int i{ }; i < amountToPlace; ++i)
		//{
		//	if (randomRows == player.GetPositionY() && randomColumns == player.GetPositionX())
		//	{
		//		std::cout << "isPlaced is true\n";
		//		isPlaced = true;
		//		continue;
		//	}
		//	else
		//	{
		//		if (isPlaced == true)
		//		{
		//			//keep looping through until all objects are placed on the map
		//			std::cout << "isPlaced was true so now we add one to amountToPlace.\n";
		//			amountToPlace++;
		//		}
		//		else 
		//		{
		//			std::cout << "isPlaced is false\n";
		//			mGameMap[randomRows][randomColumns] = object;
		//		}
		//	}
		//}
	}

private:
	const std::string mMapName{ "Map Name" };
	int mMapRows{ 5 };
	int mMapColumns{ 5 };
	const char mMapTile{ '+' };
	std::vector<std::vector<char>> mGameMap;
	char mTransitionTile{ 'H' };
	char mObject{ '#'};
};


void Secret(const Player& player);


int main()
{
	std::mt19937 mt{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
	mt.discard(1000);

	Player Hero('O', 7, 5);
	MapGenerator Field("Field", 20, 50, '-');
	std::uniform_int_distribution<> rows{0, 20};
	std::uniform_int_distribution<> columns{0, 50};

	Field.InitializeMap(Hero);

	//Temporary solution
	for (int i{ }; i < 5; ++i)
	{
		Field.DrawObjects(rows(mt), columns(mt), '&', 5, Hero);
	}

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
		Secret(Hero);
	}
}

void Player::Movement(Player::Direction choice, MapGenerator& mapGenerator) 
{
	switch (choice) 
	{
		case Direction::UP:
			if (mPosY) 
			{
				//Initialize and set mPosY to the oldY. It can be used in the update 
				//function
				const auto oldY{ mPosY-- }; //This

				//Is the same exact thing as this:
				//const auto oldY{ mPosY };
				//mPosY--;

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

//This is just a test
void Secret(const Player& player)
{
	if (player.GetPositionX() == 30 && player.GetPositionY() == 13)
	{
		std::cout << "You found a secret!\n";
	}
}