#ifndef TILES_H
#define TILES_H

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

#endif
