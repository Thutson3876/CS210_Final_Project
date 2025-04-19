#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include "MenuOption.h"
#include "City.h"
#include "BasicCache.h"

class FindOption : public MenuOption
{
	BasicCache cache = BasicCache();

public:

	FindOption() : MenuOption("Find", "Enter a city name and country code: ") {}

	void action();
};

