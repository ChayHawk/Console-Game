//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.0.52
// Version Date     : April 14th 2023 @ 11:47 AM
// Date Created     : 
// Lines of Code    : 520
// Description      : 
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

#include "Collision.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Tiles.h"
#include "Map.h"

std::mt19937 mt{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

int main()
{
	std::vector<Character> characterContainer;

	Collision collision;

	Player Hero("Hero", 'O', 5, 5);
	Enemy Goblin("Goblin", 'E', 15, 15);
	Map Field("Field", 20, 50, '.');

	characterContainer.push_back(Hero);
	characterContainer.push_back(Goblin);

	Tiles Rock('&');
	Tiles Tree('T');
	Tiles Water('=');
	Tiles Treasure('x');

	Field.Initialize(characterContainer);

	Field.DrawRandomObjects(mt, Rock, 5, Hero);
	Field.DrawRandomObjects(mt, Tree, 5, Hero);

	Field.PlaceRandomTreasure(mt, Treasure, Hero);

	int oldX{ Hero.GetXPosition()};
	int oldY{ Hero.GetYPosition()};

	while (true)
	{
		Field.Draw();
		Goblin.Move(mt, Field);

		std::cout << "Player  X: " << Hero.GetXPosition() << " Player Y: " << Hero.GetYPosition() << '\n';
		std::cout << "Player Old X: " << oldX << " Player Old Y: " << oldY << "\n\n";

		Hero.GetDirection(Hero.GetYPosition(), Hero.GetXPosition(), oldY, oldX);

		oldX = Hero.GetXPosition();
		oldY = Hero.GetYPosition();

		std::cout << "What do you want to do?\n\n";

		std::cout << "w) Move Up\n";
		std::cout << "s) Move Down\n";
		std::cout << "a) Move Left\n";
		std::cout << "d) Move Right\n";
		std::cout << "p) Dig\n";

		char choice{ };

		std::cin >> choice;

		Hero.Movement(choice, Field);
	}
}