#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
	public:
		Player(const std::string& name, char character, int posX, int posY) : Character{ name, character, posX, posY }
		{}
};

#endif