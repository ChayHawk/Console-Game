#pragma once

#include <istream>
#include <ostream>
#include <vector>

class Game
{
	public:
		Game() = default;

		void Save();
		void Load();

	private:
		std::istream mLoad;
		std::ostream mSave;

		std::vector<char> mMapList;
};