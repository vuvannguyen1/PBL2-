#include "Movie.h"


vector<Movie> loadMoviesFromCSV(const string& filePath) {
    vector<Movie> movies;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Không thể mở file: " << filePath << endl;
        return movies;
    }

    string line;
    getline(file, line); // bỏ dòng header

    while (getline(file, line)) {
        stringstream ss(line);
        Movie m;

        getline(ss, m.title, ',');
        getline(ss, m.genre, ',');
        getline(ss, m.duration, ',');
        getline(ss, m.country, ',');
        getline(ss, m.cast, ',');
        getline(ss, m.description, ',');
        getline(ss, m.posterPath, ',');

        movies.push_back(m);
    }

    file.close();
    return movies;
}
