#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include <mutex>
#include "IMenuOption.h"
#include "ICache.h"
#include "FindOption.h"
#include "CacheTypeOption.h"

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

	bool isOpened = false;

	std::vector<IMenuOption*> options;

	void tick();

public:
	Menu(const Menu& obj) = delete;

	Menu() {
		options = { new FindOption(), new CacheTypeOption() };
		cache = new BasicCache();
	}

	Menu(std::vector<IMenuOption*> menuOptions) {
		options = menuOptions;
		cache = new BasicCache();
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
};

