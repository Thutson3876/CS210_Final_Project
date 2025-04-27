#pragma once
#include "IMenuOption.h"

class CacheTypeOption : public IMenuOption
{

public:

	CacheTypeOption() : IMenuOption("Cache Type", "Choose a caching type to use: ") {}

	void action();
};

