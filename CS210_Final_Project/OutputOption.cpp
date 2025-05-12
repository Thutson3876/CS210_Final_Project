#include "OutputOption.h"
#include "Menu.h"
#include "Timer.h"

using namespace std;

void OutputOption::action() {
	auto menu = Menu::getInstance();
	auto queries = menu->generateRandomQueries();
	ICache* cache = menu->getCache();

	string cacheType = menu->getCacheName();

	Timer timer;
	

	for (auto& q : queries) {
		string countryCode = get<0>(q);
		string cityName = get<1>(q);

		bool cacheHit = true;

		double tic = timer.get_time();

		City* city = cache->lookup(countryCode + cityName);

		// not in cache
		if (city == nullptr) {

			city = menu->lookupCityFromTrie(countryCode, cityName);

			if (city == nullptr) {
				cout << countryCode << " " << cityName << " Not Found." << endl;
				continue;
			}

			cacheHit = false;
		}

		double toc = timer.get_time();

		menu->writeToOutputFile(cacheType, toc - tic, cacheHit);

		cout << "[]";
	}

	cout << endl;

	cout << "Performance test complete!" << endl;


	/*string input;
	auto menu = Menu::getInstance();
	
	cout << "Toggle Performance Tracking: 1. True | 2. False" << endl;

	cin >> input;

	if (!is_number(input)) {
		cout << "Invalid Input: Must be a number" << endl;
		return;
	}

	int i = stoi(input) - 1;

	if (i < 0 || i >= 1) {
		cout << "Invalid Input: Must be between 1 and 2" << endl;
		return;
	}

	bool doTracking = i == 1 ? true : false;

	menu->setTracking(doTracking);
	
	cout << "Performance Tracking set to " << doTracking << endl;
	*/
}