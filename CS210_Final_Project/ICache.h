#pragma once
#include <string>
#include "City.h"

class ICache {
protected:
	int maxSize = 10;

	virtual void add(City& city) = 0;

	virtual void validateSize() = 0;

public:
	virtual City* lookup(std::string key) = 0;
};