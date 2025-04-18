#pragma once
#include <string>
#include <vector>

class MenuOption
{
private:
	std::string displayName;

	std::string prompt;

	std::vector<std::string> input;

protected:
	MenuOption(std::string name, std::string promp) : displayName(name), prompt(promp) {}

public:
	std::string getDisplayName() { 
		return displayName; 
	}

	std::string getPrompt() {
		return prompt;
	}

	virtual void action() = 0;
};

