//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.3
// Version Date     : March 25th 2023 @ 9:07 AM
// Date Created     : 
// Lines of Code    : 205
// Description      : 
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <utility>

void DirectionalError();

class Map 
{
	public:
		Map(const std::string& mapName, int mapRows, int mapColumns, char mapTile) :
			mMapName(mapName), mMapRows(mapRows), mMapColumns(mapColumns), mMapTile(mapTile) {}

		void InitializeMap() 
		{
			mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));
		}

		void DrawMap(int posX, int posY, char player, int transitionX, int transitionY, char transitionCharacter)
		{
			for (int row{}; row < mMapRows; ++row) 
			{
				for (int col{}; col < mMapColumns; ++col)
				{
					mGameMap[row][col] = mMapTile;
					mGameMap[transitionY][transitionX] = transitionCharacter;
					mGameMap[posY][posX] = player;

					std::cout << mGameMap[row][col];
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

		void TransitionMaps(int transitionX, int transitionY, char transitionCharacter)
		{

		}

		int GetTransitionX() const
		{
			return mMapTransitionX;
		}

		int GetTransitionY() const
		{
			return mMapTransitionY;
		}

	private:
		const std::string mMapName{ "Map Name" };
		int mMapRows{ 5 };
		int mMapColumns{ 5 };
		const char mMapTile{ '+' };
		std::vector<std::vector<char>> mGameMap;
		int mMapTransitionX{ 0 };
		int mMapTransitionY{ 0 };
		char mMapTransitionCharacter{ 'Z' };
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
			Field.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayer(), 7, 5, 'Z');
		}
		else if(Hero.GetPositionX() == 7 && Hero.GetPositionY() == 6)
		{
			Courtyard.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayer(), 7, 6, 'Z');
		}
		else 
		{
			Courtyard.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayer(), 7, 6, 'Z');
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