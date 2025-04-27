#pragma once
#include "ICache.h"
#include <unordered_map>

class RRCache : public ICache
{
private:
	void add(City& city);

	void validateSize();
};

