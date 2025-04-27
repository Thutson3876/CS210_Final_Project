#include "Menu.h"
#include "FindOption.h"

Menu* Menu::instancePtr = nullptr;
std::mutex Menu::mtx;

int main() {
	auto options = std::vector<IMenuOption*>();
	options.push_back(new FindOption());

	Menu* menu = Menu::getInstance();
	
	menu->open();

}