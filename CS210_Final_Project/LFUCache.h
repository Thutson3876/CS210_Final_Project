#pragma once
#include "ICache.h"
#include <unordered_map>
#include <queue>

class LFUCache : public ICache
{
private:
	std::unordered_map<std::string, int> frequencyMap = {};

	void add(City& city);

	void validateSize();

};

