#include "Movie.h"

// Hàm helper để parse CSV field có thể chứa dấu phẩy trong quotes
string parseCSVField(stringstream& ss) {
    string field;
    char ch;
    bool inQuotes = false;
    
    while (ss.get(ch)) {
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            break;
        } else {
            field += ch;
        }
    }
    
    return field;
}

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

        // Đọc tất cả các field theo thứ tự trong CSV
        // film_id,title,age_rating,country,language,genres,duration_min,release_date,director,cast,synopsis,poster_path,status
        
        m.film_id = parseCSVField(ss);
        m.title = parseCSVField(ss);
        m.age_rating = parseCSVField(ss);
        m.country = parseCSVField(ss);
        m.language = parseCSVField(ss);
        m.genres = parseCSVField(ss);
        m.duration_min = parseCSVField(ss);
        m.release_date = parseCSVField(ss);
        m.director = parseCSVField(ss);
        m.cast = parseCSVField(ss);
        m.synopsis = parseCSVField(ss);
        m.poster_path = parseCSVField(ss);
        
        // Field cuối cùng không có dấu phẩy sau
        getline(ss, m.status);

        movies.push_back(m);
    }

    file.close();
    cout << "Đã tải " << movies.size() << " phim từ file CSV." << endl;
    return movies;
}


