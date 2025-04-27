#include "ICache.h"

City* ICache::lookup(std::string key) {
	auto foundCity = map.find(key);

	// City not in cache
	if (foundCity == map.end()) {
		return nullptr;
	}

	return foundCity->second;
}