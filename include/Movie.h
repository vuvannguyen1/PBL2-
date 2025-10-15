#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Movie {
    string film_id;
    string title;
    string age_rating;
    string country;
    string language;
    string genres;
    string duration_min;
    string release_date;
    string director;
    string cast;
    string synopsis;
    string poster_path;
    string status;
};

vector<Movie> loadMoviesFromCSV(const string& filePath);
void testMovieCSV();  // Hàm test đọc CSV

