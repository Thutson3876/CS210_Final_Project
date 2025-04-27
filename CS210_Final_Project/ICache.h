#pragma once
#include <string>
#include "City.h"
#include <unordered_map>
#include <map>

class ICache {
protected:
	int maxSize = 10;

	std::unordered_map<std::string, City*> map = {};

	virtual void add(City& city) = 0;

	virtual void validateSize() = 0;

	std::string generateKey(City& city) {
		return city.countryCode + city.name;
	}

public:
	City* lookup(std::string key);
};