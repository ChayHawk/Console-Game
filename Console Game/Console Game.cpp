//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.0.20
// Version Date     : April 1st 2023 @ 3:09 AM
// Date Created     : 
// Lines of Code    : 253
// Description      : 
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

class MapGenerator;

class Character
{
	public:
		Character(const std::string& name, char character, int posX, int posY) : mName(name), mCharacter(character), mPosX(posX), mPosY(posY) {}

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

		char GetCharacter() const
		{
			return mCharacter;
		}

		std::string GetName() const
		{
			return mName;
		}

		void Movement(Character::Direction choice, MapGenerator& mapGenerator);

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

	private:

};

class Enemy : public Character
{
	public:
		Enemy(const std::string& name, char character, int posX, int posY): Character{name, character, posX, posY}
		{}

		void Move(std::mt19937& mt, MapGenerator& mapGenerator)
		{
			//Randomize directions
			std::uniform_int_distribution<> moveEnemy{ 1, 4};

			Movement(static_cast<Character::Direction>(moveEnemy(mt)), mapGenerator);
		}

	private:
};

class MapGenerator
{
	public:
		MapGenerator(const std::string& mapName, int mapRows, int mapColumns, char mapTile) :
			mMapName(mapName), mMapRows(mapRows), mMapColumns(mapColumns), mMapTile(mapTile) {}

		void InitializeMap(const std::vector<Character>& characters)
		{
			mGameMap.assign(mMapRows, std::vector<char>(mMapColumns, mMapTile));

			for (const auto& character : characters)
			{
				const int row{ character.GetPositionY() };
				const int col{ character.GetPositionX() };
				const char ch{ character.GetCharacter() };

				mGameMap[row][col] = ch;
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

		size_t MaxRows() const
		{
			return mGameMap.size();
		}

		size_t MaxColumns() const
		{
			return !mGameMap.empty() ? mGameMap[0].size() : 0;
		}

		void DrawObjects(std::mt19937& mt, char object, int amountToPlace, const Character& character)
		{
	
			std::uniform_int_distribution<> rows{0, 19};
			std::uniform_int_distribution<> columns{0, 49};

			for (int i{ }; i < amountToPlace; ++i)
			{
				//Do not draw over player
				if (rows(mt) != character.GetPositionX() && rows(mt) != character.GetPositionY() || columns(mt) != character.GetPositionX() && columns(mt) != character.GetPositionY())
				{
					mGameMap[rows(mt)][columns(mt)] = object;
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
	MapGenerator Field("Field", 20, 50, '-');

	characterContainer.push_back(Hero);
	characterContainer.push_back(Goblin);

	Field.InitializeMap(characterContainer);
	Field.DrawObjects(mt, '&', 10, Hero);

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

void Character::Movement(Character::Direction choice, MapGenerator& mapGenerator)
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

				mapGenerator.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case Direction::DOWN:
			if (mPosY < mapGenerator.MaxRows() - 1)
			{
				const auto oldY{ mPosY++ };

				mapGenerator.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case Direction::LEFT:
			if (mPosX)
			{
				const auto oldX{ mPosX-- };

				mapGenerator.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case Direction::RIGHT:
			if (mPosX < mapGenerator.MaxColumns() - 1)
			{
				const auto oldX{ mPosX++ };

				mapGenerator.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
				mapGenerator.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		default:
			std::cout << "Invalid Input\n";
			return;
	}
}