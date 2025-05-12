#include "Menu.h"
#include "Utils.h"
#include "ICache.h"
#include "LFUCache.h"
#include "RRCache.h"
#include <iostream>
#include <fstream> 

using namespace std;

void Menu::populateTrie() {
	std::ifstream file(filePath);
	std::string line, word;

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filePath << std::endl;
		return;
	}

	print("Populating trie with data from " + filePath + "...");

	// clear the first line since it has no useful data
	getline(file, line);

	while (getline(file, line)) {
		std::stringstream ss(line);
		std::vector<std::string> row;
		while (getline(ss, word, ',')) {
			row.push_back(word);
		}

		trie->insert(row[0] + row[1], stod(row[2]));
	}
	print("Trie populated!");

	file.close();
}

City* Menu::lookupCityFromFile(std::string& countryCode, std::string& cityName) {
	std::ifstream file(filePath);
	std::string line, word;

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filePath << std::endl;
		return nullptr;
	}

	while (getline(file, line)) {
		std::stringstream ss(line);
		std::vector<std::string> row;
		while (getline(ss, word, ',')) {
			row.push_back(word);
		}
		if (row[0] == countryCode && row[1] == cityName)
			return new City(countryCode, cityName, stod(row[2]));
	}
	file.close();

	return nullptr;
}

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
		outputFileName = "LFU.csv";
		cacheName = "LFU";
		break;
	case FIFO:
		cache = new BasicCache();
		outputFileName = "FIFO.csv";
		cacheName = "FIFO";
		break;
	case RR:
		cache = new RRCache();
		outputFileName = "RR.csv";
		cacheName = "RR";
		break;
	default:
		break;
	}
}

ICache* Menu::getCache() {
	return cache;
}

void Menu::writeToOutputFile(std::string& cacheType, double lookupTime, bool hitCache) {
	
	std::ifstream infile(outputFileName);

	// If the file doesn't exist yet, add header info
	if (!infile.good()) {
		std::ofstream outfile(outputFileName);
		outfile << "Cache Type, Lookup Time, Cache Hit" << endl;
		outfile.close();
	}

	writeCSV(outputFileName, cacheType, hitCache, lookupTime);
}
