#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include "IMenuOption.h"
#include "City.h"
#include "BasicCache.h"

class FindOption : public IMenuOption
{

public:

	FindOption() : IMenuOption("Find", "Enter a city name and country code: ") {}

	void action();
};

