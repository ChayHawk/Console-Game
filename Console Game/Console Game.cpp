//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.0.26
// Version Date     : April 7nd 2023 @ 8:32 AM
// Date Created     : 
// Lines of Code    : 263
// Description      : 
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

class Map;
class Collision;
class Tiles;

class Character
{
	public:
		Character(const std::string& name, char character, int posX, int posY) : mName(name), mCharacter(character), mPosX(posX), mPosY(posY) {}

		enum class Direction
		{
			UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
		};

		int GetPositionX() const { return mPosX; }
		int GetPositionY() const { return mPosY; }
		char GetCharacter() const { return mCharacter; }
		std::string GetName() const { return mName; }

		void Movement(Character::Direction choice, Map& map);

	private:
		std::string mName{ "Character" };
		const char mCharacter{ 'C' };
		int mPosX{ };
		int mPosY{ };
};


class Player : public Character
{
	public:
		Player(const std::string& name, char character, int posX, int posY) : Character{name, character, posX, posY}
		{}
};

class Enemy : public Character
{
	public:
		Enemy(const std::string& name, char character, int posX, int posY): Character{name, character, posX, posY}
		{}

		void Move(std::mt19937& mt, Map& map)
		{
			//Randomize directions
			std::uniform_int_distribution<> moveEnemy{ 1, 4};

			Movement(static_cast<Character::Direction>(moveEnemy(mt)), map);
		}
};

class Tiles
{
	public:
		Tiles(char tile) : mTile(tile)
		{}

		int GetXPosition() const
		{
			return mXpos;
		}

		int GetYPosition() const
		{
			return mYPos;
		}

		char GetTile() const
		{
			return mTile;
		}

	private:
		char mTile{ 'X' };
		int mXpos{ 0 };
		int mYPos{ 0 };
};

class Map
{
	public:
		Map(const std::string& mapName, int mapRows, int mapColumns, char mapTile) :
			mMapName(mapName), mMapRows(mapRows), mMapColumns(mapColumns), mMapTile(mapTile) {}

		void Initialize(const std::vector<Character>& character)
		{
			mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));

			for (auto& i : character)
			{
				mGameMap[i.GetPositionY()][i.GetPositionX()] = i.GetCharacter();
			}
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

		void Update(size_t oldX, size_t oldY, size_t newX, size_t newY, char character)
		{
			mGameMap[oldY][oldX] = mMapTile;
			mGameMap[newY][newX] = character;
		}

		size_t GetMaxRows() const
		{
			return mGameMap.size();
		}

		size_t GetMaxColumns() const
		{
			return !mGameMap.empty() ? mGameMap[0].size() : 0;
		}

		void DrawRandomObjects(std::mt19937& mt, const Tiles& tile, int amountToPlace, Character& character)
		{
	
			std::uniform_int_distribution<> rows{0, mMapRows - 1};
			std::uniform_int_distribution<> columns{0, mMapColumns - 1};

			for (int i{ }; i < amountToPlace; ++i)
			{
				//if object is equal to the players position, do not draw it, we dont want an object
				//to be drawn over the player.
				if (rows(mt) != character.GetPositionX() && rows(mt) != character.GetPositionY() || columns(mt) != character.GetPositionX() && columns(mt) != character.GetPositionY())
				{
					mGameMap[rows(mt)][columns(mt)] = tile.GetTile();
				}
			}
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



int main()
{
	std::mt19937 mt{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

	std::vector<Character> characterContainer;

	Player Hero("Hero", 'O', 5, 5);
	Enemy Goblin("Goblin", 'X', 15, 15);
	Map Field("Field", 20, 50, '-');

	characterContainer.push_back(Hero);
	characterContainer.push_back(Goblin);

	std::vector<Tiles> tileContainer;

	Tiles Rock('&');
	Tiles Tree('T');

	tileContainer.push_back(Rock);
	tileContainer.push_back(Tree);

	Field.Initialize(characterContainer);
	Field.DrawRandomObjects(mt, Rock, 10, Hero);



	while (true)
	{
		Field.DrawMap();
		Goblin.Move(mt, Field);

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

void Character::Movement(Character::Direction choice, Map& map)
{
	switch (choice)
	{
		case Direction::UP:
			if (mPosY)
			{
				const auto oldY{ mPosY-- }; //This

				map.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case Direction::DOWN:
			if (mPosY < map.GetMaxRows() - 1)
			{
				const auto oldY{ mPosY++ };

				map.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case Direction::LEFT:
			if (mPosX)
			{
				const auto oldX{ mPosX-- };

				map.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case Direction::RIGHT:
			if (mPosX < map.GetMaxColumns() - 1)
			{
				const auto oldX{ mPosX++ };

				map.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		default:
			std::cout << "Invalid Input\n";
			return;
	}
}