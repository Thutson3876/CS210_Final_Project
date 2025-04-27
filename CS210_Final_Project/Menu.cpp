#include "Menu.h"
#include "Utils.h"
#include "ICache.h"
#include "LFUCache.h"
#include "RRCache.h"
#include <iostream>

using namespace std;

void Menu::tick() {
	string input;

	cout << "Choose a menu option: ";
	int i = 0;
	for (; i < options.size(); i++) {
		cout << (i + 1) << ". " << options[i]->getDisplayName() << " | ";
	}
	cout << (i + 1) << ". Close" << endl;

	cin >> input;

	if (!is_number(input)) {
		cout << "Invalid Input: Must be a number" << endl;
		return;
	}

	i = stoi(input) - 1;

	if (i == options.size()) {
		isOpened = false;
		cout << "Shutting down..." << endl;
		return;
	}
	else if (i < 0 || i > options.size()) {
		cout << "Invalid Input: Must be between 0 and " << (options.size() - 1) << endl;
		return;
	}

	cout << options[i]->getPrompt() << endl;
	options[i]->action();
}

void Menu::open() {
	isOpened = true;

	while (isOpened) {
		tick();
	}
}

void Menu::close() {
	isOpened = false;
}

void Menu::setCache(CacheType type) {
	if (cache != nullptr) {
		delete cache;
	}
	
	switch (type)
	{
	case LFU:
		cache = new LFUCache();
		break;
	case FIFO:
		cache = new BasicCache();
		break;
	case RR:
		cache = new RRCache();
		break;
	default:
		break;
	}
}

ICache* Menu::getCache() {
	return cache;
}
