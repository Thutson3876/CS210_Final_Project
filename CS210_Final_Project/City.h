#pragma once
#include <format> 

struct City {
	std::string countryCode = "";
	std::string name = "";
	double population = 0.0;

	City() {}

	City(std::string countryCode, std::string cityName, double pop) {
		name = cityName;
		this->countryCode = countryCode;
		population = pop;
	}

	operator std::string() const {
		return "Country Code: " + countryCode + "\nCity Name: " + name + " \nPopulation: " + std::to_string(population);
	}
};
