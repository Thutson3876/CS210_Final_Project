#pragma once
#include "IMenuOption.h"

class OutputOption : public IMenuOption
{
public:

	OutputOption() : IMenuOption("Performance Test", "Running performance test...") {}

	void action();
};

