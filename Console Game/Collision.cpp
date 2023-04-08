#include "Collision.h"

Collision::Collision()
{

}

//This does not yet check for map bound collision
bool Collision::CheckCollision(int playerX, int playerY, const std::vector<Tiles>& tiles)
{
    for (auto& i : tiles)
    {
        if (playerX == i.GetXPosition() || playerY == i.GetYPosition())
        {
            std::cout << "Collision Detected\n";
            return true;
        }
    }
    return false;
}