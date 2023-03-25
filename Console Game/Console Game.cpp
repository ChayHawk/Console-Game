//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.0
// Version Date     : March 25th 2023 @ 6:01 AM
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
		Map(const std::string& mapName, size_t mapRows, size_t mapColumns, char mapTile) :
			mMapName(mapName), mMapRows(mapRows), mMapColumns(mapColumns), mMapTile(mapTile) {}

		void InitializeMap() 
		{
			mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));
		}

		void DrawMap(size_t posX, size_t posY, char player) 
		{
			for (size_t row{}; row < mMapRows; ++row) 
			{
				for (size_t col{}; col < mMapColumns; ++col) 
				{
					mGameMap[row][col] = mMapTile;
					mGameMap[posY][posX] = player;

					std::cout << mGameMap[row][col];
				}
				std::cout << '\n';
			}
		}

		size_t maxRow() const 
		{
			return mGameMap.size();
		}

		size_t maxCol() const 
		{
			return !mGameMap.empty() ? mGameMap[0].size() : 0;
		}

	private:
		const std::string mMapName{ "Map Name" };
		size_t mMapRows{ 5 };
		size_t mMapColumns{ 5 };
		const char mMapTile{ '+' };
		const char mMapTransition{ 'Z' }; //UNUSED: Transition from one map to another whn player touches this
		std::vector<std::vector<char>> mGameMap;
};

//Can promote to a character class when i learn virtual, then inherit from there.
class Player 
{
	public:
		Player(char player, size_t posX, size_t posY) : mPlayer(player), mPosX(posX), mPosY(posY) {}

		size_t GetPositionX() const 
		{
			return mPosX;
		}

		size_t GetPositionY() const 
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
		size_t mPosX{ };
		size_t mPosY{ };
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