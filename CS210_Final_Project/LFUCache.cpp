#include "LFUCache.h"

using namespace std;

void LFUCache::add(City& city) {
	string key = generateKey(city);
	auto foundCity = map.find(key);

	// City already in cache
	if (foundCity != map.end()) {
		frequencyMap[key]++;
		return;
	}

	map.insert({ key, &city });
	frequencyMap[key]++;

	validateSize();
}

void LFUCache::validateSize() {
	int sizeDiff = map.size() - maxSize;
	if (sizeDiff <= 0)
		return;

	for (int i = 0; i < sizeDiff; i++) {
		std::unordered_map<string, int>::iterator it
			= std::min_element(frequencyMap.begin(), frequencyMap.end(), [](const std::pair<string, int>& a, const std::pair<string, int>& b)->bool { return a.second < b.second; });
		string key = it->first;
		map.erase(key);
		frequencyMap.erase(key);
	}
}