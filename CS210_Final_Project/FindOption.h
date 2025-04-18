#pragma once
#include "MenuOption.h"

class FindOption : public MenuOption
{
public:
	FindOption() : MenuOption("Find", "Enter a city name and country code: ") {}

	void action();
};

