#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Movie {
    string title;
    string genre;
    string duration;
    string country;
    string cast;
    string description;
    string posterPath;
};

std::vector<Movie> loadMoviesFromCSV(const std::string& filePath);

