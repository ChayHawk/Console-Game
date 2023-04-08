#ifndef TILES_H
#define TILES_H

class Tiles
{
	public:
		Tiles(char tile) : mTile(tile)
		{}

		int GetXPosition() const;
		int GetYPosition() const;
		char GetTile() const;

	private:
		char mTile{ 'X' };
		int mXpos{ 0 };
		int mYPos{ 0 };
};

#endif