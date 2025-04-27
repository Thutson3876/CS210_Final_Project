#include "CacheTypeOption.h"
#include <iostream>
#include <istream>
#include <iomanip>
#include "City.h"
#include "Menu.h"

using namespace std;

void CacheTypeOption::action() {
	string input;
	int i = 0;
	auto allTypes = Menu::getInstance()->getAllCacheTypes();
	auto typeNames = Menu::getInstance()->getAllCacheNames();

	for (; i < allTypes.size(); i++) {
		cout << (i + 1) << ". " << typeNames[i];
		if (i < allTypes.size() - 1)
			cout << " | ";
	}

	cout << endl;

	cin >> input;

	if (!is_number(input)) {
		cout << "Invalid Input: Must be a number" << endl;
		return;
	}

	i = stoi(input) - 1;

	if (i < 0 || i >= allTypes.size()) {
		cout << "Invalid Input: Must be between 0 and " << allTypes.size() << endl;
		return;
	}

	CacheType type = static_cast<CacheType>(i);

	Menu::getInstance()->setCache(type);

	cout << typeNames[i] << " Selected!" << endl;
}