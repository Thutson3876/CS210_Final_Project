#include "OutputOption.h"
#include "Menu.h"
#include "Timer.h"

using namespace std;

static std::vector<std::tuple<std::string, std::string>> randomQueries;

// Figure out why cache is always missing
void OutputOption::action() {
	auto menu = Menu::getInstance();

	if(randomQueries.size() == 0)
		randomQueries = menu->generateRandomQueries();

	ICache* cache = menu->getCache();

	string cacheType = menu->getCacheName();

	Timer timer;
	
	for (auto& q : randomQueries) {
		string countryCode = get<0>(q);
		string cityName = get<1>(q);

		bool cacheHit = true;

		std::cout << "[";

		double tic = timer.get_time();

		City* city = cache->lookup(countryCode + cityName);

		// not in cache
		if (city == nullptr) {

			city = menu->lookupCityFromTrie(countryCode, cityName);

			if (city == nullptr) {
				std::cout << countryCode << " " << cityName << " Not Found." << endl;
				continue;
			}

			cacheHit = false;

			std::cout << "miss";
		}
		else {
			std::cout << "hit";
		}

		double toc = timer.get_time();

		menu->writeToOutputFile(cacheType, toc - tic, cacheHit);

		cache->add(*city);

		std::cout << "]";
	}

	std::cout << endl;

	std::cout << "Performance test complete!" << endl;
}