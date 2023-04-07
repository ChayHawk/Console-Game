//============================================================================
// Name             : Console Game
// Author           : Chay Hawk
// Version          : 0.1.0.28
// Version Date     : April 7nd 2023 @ 12:06 PM
// Date Created     : 
// Lines of Code    : 263
// Description      : 
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Tiles.h"
#include "Map.h"
#include "Collision.h"

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

		std::cout << "X: " << Hero.GetXPosition() << " Y: " << Hero.GetYPosition() << "\n\n";

		std::cout << "What do you want to do?\n\n";

		std::cout << "1) Move Up\n";
		std::cout << "2) Move Down\n";
		std::cout << "3) Move Left\n";
		std::cout << "4) Move Right\n";

		int choice{ };

		std::cin >> choice;
		Hero.Movement(static_cast<Player::Direction>(choice), Field);
		Hero.GetDirection(Field);
	}
}