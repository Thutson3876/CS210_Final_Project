#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include "MenuOption.h"

class Menu
{
private:
	bool isOpened = false;

	std::vector<MenuOption*> options;

	void tick();

public:
	Menu(std::vector<MenuOption*> menuOptions) {
		options = menuOptions;
	}

	void open();

	void close();
};

