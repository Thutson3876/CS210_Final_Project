#pragma once
#include <unordered_map>
#include <queue>
#include "ICache.h"
#include "Utils.h"

class BasicCache : public ICache
{
private:
	std::queue<std::string> queue = {};

	void validateSize();
public:
	void add(City& city);
};

