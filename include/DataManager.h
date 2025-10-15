#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "MovieRepo.h"

class DataManager {
private:
    static std::string basePath;
    static std::string trim(const std::string& s);

public:
    // ========== SETUP ==========
    static void setBasePath(const std::string& path);
    static std::string getBasePath();
    
    // ========== UTILITY ==========
    static std::string getCurrentDateTime();
    static std::string getCurrentDate();
    
    // ========== MOVIE OPERATIONS ==========
    static bool loadMovies(MovieRepo& repo, const std::string& filename = "film.csv");
    static const Movie* getMovieById(const MovieRepo& repo, const std::string& filmId);
    static std::vector<const Movie*> getMoviesByStatus(const MovieRepo& repo, const std::string& status);
    
    // ========== GENERIC CSV OPERATIONS ==========
    // Đọc CSV thành vector of maps (key = column name, value = cell value)
    static std::vector<std::unordered_map<std::string, std::string>> 
        loadCSV(const std::string& filename);
    
    // Lưu data vào CSV
    static bool saveCSV(const std::string& filename,
                       const std::vector<std::string>& headers,
                       const std::vector<std::vector<std::string>>& rows);
    
    // ========== FUTURE: USER/BOOKING OPERATIONS ==========
    // Có thể thêm sau:
    // static bool loadUsers(...)
    // static bool loadBookings(...)
    // static bool loadShowtimes(...)
};