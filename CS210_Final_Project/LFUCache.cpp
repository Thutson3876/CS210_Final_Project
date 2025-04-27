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
	queue.push_back(key);

	validateSize();
}

void LFUCache::validateSize() {
	int sizeDiff = map.size() - maxSize;
	if (sizeDiff <= 0)
		return;

	for (int i = 0; i < sizeDiff; i++) {
		int lowest = 999999;
		string lowestKey = "";
		for (auto it = queue.begin(); it != queue.end(); it++)
		{
			int curr = frequencyMap[*it];
			if (curr < lowest) {
				lowest = curr;
				lowestKey = *it;
			}
		}

		map.erase(lowestKey);
		frequencyMap.erase(lowestKey);
		queue.erase(remove(queue.begin(), queue.end(), lowestKey), queue.end());
	}
}