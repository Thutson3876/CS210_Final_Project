#include "Menu.h"
#include "FindOption.h"


int main() {
	auto options = std::vector<MenuOption*>();
	options.push_back(new FindOption());

	Menu menu = Menu(options);
	
	menu.open();

}