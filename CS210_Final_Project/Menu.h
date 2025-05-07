#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <mutex>
#include "IMenuOption.h"
#include "ICache.h"
#include "FindOption.h"
#include "CacheTypeOption.h"
#include "Trie.h"
#include "Utils.h"

enum CacheType {
	LFU,
	FIFO,
	RR
};

class Menu
{
private:
	static Menu* instancePtr;

	static std::mutex mtx;

	ICache* cache = nullptr;

	Trie* trie = nullptr;

	bool isOpened = false;

	std::vector<IMenuOption*> options;

	void tick();

	void populateTrie() {
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

public:
	Menu(const Menu& obj) = delete;

	Menu() {
		options = { new FindOption(), new CacheTypeOption() };
		cache = new BasicCache();
		trie = new Trie();
		populateTrie();
	}

	Menu(std::vector<IMenuOption*> menuOptions) {
		options = menuOptions;
		cache = new BasicCache();
		trie = new Trie();
		populateTrie();
	}

	static Menu* getInstance() {
		if (instancePtr == nullptr) {
			std::lock_guard<std::mutex> lock(mtx);
			if (instancePtr == nullptr) {
				instancePtr = new Menu();
			}
		}
		return instancePtr;
	}

	void open();

	void close();

	void setCache(CacheType type);

	ICache* getCache();

	const std::vector<CacheType> getAllCacheTypes() {
		return { LFU, FIFO, RR };
	}

	const std::vector<std::string> getAllCacheNames() {
		return { "LFU", "FIFO", "Random Replacement"};
	}

	static City* lookupCityFromFile(std::string countryCode, std::string cityName) {
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

	City* lookupCityFromTrie(std::string countryCode, std::string cityName){
		return trie->search(countryCode + cityName);
	}
};

