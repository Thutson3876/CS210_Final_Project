#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "City.h"

static const std::string filePath = "world_cities.csv";

static bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
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