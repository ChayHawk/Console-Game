//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.1
// Version Date     : March 25th 2023 @ 6:09 AM
// Date Created     : 
// Lines of Code    : 169
// Description      : 
//============================================================================

#include <iostream>
#include <vector>

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

		void DrawMap(int posX, int posY, char player) 
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
		}

		int maxRow() const
		{
			return mGameMap.size();
		}

		int maxCol() const
		{
			return !mGameMap.empty() ? mGameMap[0].size() : 0;
		}

	private:
		const std::string mMapName{ "Map Name" };
		int mMapRows{ 5 };
		int mMapColumns{ 5 };
		const char mMapTile{ '+' };
		const char mMapTransition{ 'Z' }; //UNUSED: Transition from one map to another whn player touches this
		std::vector<std::vector<char>> mGameMap;
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

		char GetPlayerSprite() const 
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
	Map Courtyard("Courtyard", 20, 50, '-');

	Courtyard.InitializeMap();

	while (true) 
	{
		Courtyard.DrawMap(Hero.GetPositionX(), Hero.GetPositionY(), Hero.GetPlayerSprite());

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
			if (mPosY < map.maxRow() - 1) 
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
			if (mPosX < map.maxCol() - 1) 
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