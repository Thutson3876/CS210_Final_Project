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

static void print(const std::string& s) {
    std::cout << s << std::endl;
}