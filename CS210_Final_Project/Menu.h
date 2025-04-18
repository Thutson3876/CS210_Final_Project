#pragma once
#include <vector>
#include "MenuOption.h"

class Menu
{
private:
	bool isOpened = false;

	std::vector<MenuOption> options;

	void tick();

public:
	void open();

	void close();
};

