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
#include "OutputOption.h"
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

	std::string cacheName = "";

	Trie* trie = nullptr;

	bool isOpened = false;

	bool doTracking = false;

	std::vector<IMenuOption*> options;

	std::string outputFileName = "";

	void tick();

	void populateTrie();

public:
	Menu(const Menu& obj) = delete;

	Menu() {
		options = { new FindOption(), new CacheTypeOption(), new OutputOption() };
		cache = new BasicCache();
		cacheName = "FIFO";
		trie = new Trie();
		populateTrie();
	}

	Menu(std::vector<IMenuOption*> menuOptions) {
		options = menuOptions;
		cache = new BasicCache();
		cacheName = "FIFO";
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

	std::string getCacheName() {
		return cacheName;
	}

	const std::vector<CacheType> getAllCacheTypes() {
		return { LFU, FIFO, RR };
	}

	const std::vector<std::string> getAllCacheNames() {
		return { "LFU", "FIFO", "Random Replacement"};
	}

	static City* lookupCityFromFile(std::string& countryCode, std::string& cityName);

	City* lookupCityFromTrie(std::string& countryCode, std::string& cityName){
		return trie->search(countryCode + cityName);
	}

	City* getRandomCity() {
		return trie->randomSearch();
	}

	std::vector<std::tuple<std::string, std::string>> generateRandomQueries(int count = 1000) {
		std::vector<std::tuple<std::string, std::string>> returnVector;

		for (int i = 0; i < count; i++) {
			City* city = getRandomCity();

			returnVector.push_back({ city->countryCode, city->name });

			delete city;
		}

		return returnVector;
	}

	void setTracking(bool doTracking) {
		this->doTracking = doTracking;
	}

	void writeToOutputFile(std::string& cacheType, double lookupTime, bool hitCache);

};

