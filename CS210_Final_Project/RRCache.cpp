#include "RRCache.h"

using namespace std;

void RRCache::add(City& city) {
	string key = generateKey(city);
	auto foundCity = map.find(key);

	// City already in cache
	if (foundCity != map.end()) {
		return;
	}

	map.insert({ key, &city });

	validateSize();
}

void RRCache::validateSize() {
	int sizeDiff = map.size() - maxSize;
	if (sizeDiff <= 0)
		return;

	for (int i = 0; i < sizeDiff; i++) {
		
		auto it = map.begin();
		std::advance(it, rand() % map.size());

		string key = it->first;
		map.erase(key);
	}
}
