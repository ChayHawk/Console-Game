#pragma once

#include <string>

class Item
{
	public:
		Item(const std::string& name): mName(name)
		{}

	private:
		std::string mName{ "Item Name" };
		int mValue{ 0 };
};

