#include "FindOption.h"
#include <iostream>
#include <istream>
#include <iomanip>

using namespace std;

void FindOption::action() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter country code: ";
	string countryCode;
	getline(cin, countryCode);

	cout << "Enter city name: ";
	string cityName;
	getline(cin, cityName);
	cin.clear();

	string key = countryCode + cityName;

	City* city = cache.lookup(key);

	// not in cache
	if (city == nullptr) {
		city = lookupCityFromFile(countryCode, cityName);

		if (city == nullptr) {
			cout << countryCode << " " << cityName << " Not Found." << endl;
			return;
		}
	}

	cout << "City Found!" << endl;
	cout << city->operator std::string() << endl;
}
