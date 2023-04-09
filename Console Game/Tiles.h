#ifndef TILES_H
#define TILES_H

class Tiles
{
	public:
		Tiles(char tile, int xPos, int yPos) : mTile(tile), mXpos(xPos), mYpos(yPos)
		{}

		Tiles(char tile) : mTile(tile)
		{}

		int GetXPosition() const;
		int GetYPosition() const;
		char GetTile() const;

	private:
		char mTile{ 'X' };
		int mXpos{ 0 };
		int mYpos{ 0 };
};

#endif