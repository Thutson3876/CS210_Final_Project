#include "BasicCache.h"
#include "Utils.h"

using namespace std;

void BasicCache::add(City& city) {
	string key = generateKey(city);
	auto foundCity = map.find(key);

	// City already in cache
	if (foundCity != map.end()) {
		return;
	}

	map.insert({ key, &city });
	queue.push(key);

	validateSize();
}

void BasicCache::validateSize() {
	int sizeDiff = queue.size() - maxSize;
	if (sizeDiff <= 0)
		return;

	for (int i = 0; i < sizeDiff; i++) {
		string key = queue.front();
		map.erase(key);

		queue.pop();
	}
}

City* BasicCache::lookup(string key) {
	auto foundCity = map.find(key);

	// City not in cache
	if (foundCity == map.end()) {
		return nullptr;
	}

	return foundCity->second;
}
