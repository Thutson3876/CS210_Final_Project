#pragma once
#include "ICache.h"
#include <unordered_map>

class RRCache : public ICache
{
private:

	void validateSize();
public:
	void add(City& city);

};

