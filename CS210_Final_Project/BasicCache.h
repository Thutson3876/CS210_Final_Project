#pragma once
#include <unordered_map>
#include <queue>
#include "ICache.h"
#include "Utils.h"

class BasicCache : public ICache
{
private:
	std::unordered_map<std::string, City*> map = {};
	std::queue<std::string> queue = {};

	std::string generateKey(City& city) {
		return city.countryCode + city.name;
	}

	void add(City& city);

	void validateSize();

public:
	City* lookup(std::string key);
};

