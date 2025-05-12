#include "Menu.h"
#include "FindOption.h"

Menu* Menu::instancePtr = nullptr;
std::mutex Menu::mtx;

int main() {
	Menu* menu = Menu::getInstance();
	
	menu->open();

}