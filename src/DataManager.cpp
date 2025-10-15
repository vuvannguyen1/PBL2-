#include "DataManager.h"
#include "CsvReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <filesystem>

std::string DataManager::basePath = "data/";

// ========== SETUP ==========

void DataManager::setBasePath(const std::string& path) {
    basePath = path;
    if(!basePath.empty() && basePath.back() != '/' && basePath.back() != '\\') {
        basePath += "/";
    }
}

std::string DataManager::getBasePath() {
    return basePath;
}

// ========== UTILITY ==========

std::string DataManager::trim(const std::string& s) {
    std::string result = s;
    // Xóa ký tự thừa ở cuối
    while(!result.empty() && (result.back() == '\r' || result.back() == '\n' || 
                              result.back() == ' ' || result.back() == '\t')) {
        result.pop_back();
    }
    // Xóa ký tự thừa ở đầu
    size_t i = 0;
    while(i < result.size() && (result[i] == ' ' || result[i] == '\t')) {
        ++i;
    }
    return result.substr(i);
}

std::string DataManager::getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", timeinfo);
    return std::string(buffer);
}

std::string DataManager::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return std::string(buffer);
}

// ========== MOVIE OPERATIONS ==========

bool DataManager::loadMovies(MovieRepo& repo, const std::string& filename) {
    std::string primaryPath = basePath + filename;
    if (repo.loadFromCsv(primaryPath)) {
        return true;
    }
    
    // Thử path thay thế (../data/...)
    std::string fallbackPath = "../" + basePath + filename;
    if (repo.loadFromCsv(fallbackPath)) {
        return true;
    }
    
    std::cerr << "❌ Không thể load movies từ '" << primaryPath 
              << "' hoặc '" << fallbackPath << "'" << std::endl;
    return false;
}

const Movie* DataManager::getMovieById(const MovieRepo& repo, const std::string& filmId) {
    return repo.findById(filmId);
}

std::vector<const Movie*> DataManager::getMoviesByStatus(const MovieRepo& repo, const std::string& status) {
    std::vector<const Movie*> result;
    
    // Duyệt qua tất cả movies trong repo
    // Note: MovieRepo cần thêm method getAllMovies() hoặc iterator
    // Hiện tại trả về empty vector
    
    return result;
}

// ========== GENERIC CSV OPERATIONS ==========

std::vector<std::unordered_map<std::string, std::string>> 
DataManager::loadCSV(const std::string& filename) {
    std::vector<std::unordered_map<std::string, std::string>> result;
    
    std::string filepath = basePath + filename;
    CsvReader reader(filepath);
    
    if (!reader.isValid()) {
        // Thử fallback path
        filepath = "../" + basePath + filename;
        CsvReader reader2(filepath);
        
        if (!reader2.isValid()) {
            std::cerr << "❌ Không thể đọc CSV: " << filename << std::endl;
            return result;
        }
        
        reader2.each([&result](const std::unordered_map<std::string, std::string>& row) {
            result.push_back(row);
        });
        
        return result;
    }
    
    reader.each([&result](const std::unordered_map<std::string, std::string>& row) {
        result.push_back(row);
    });
    
    std::cout << "✅ Đã load " << result.size() << " dòng từ " << filename << std::endl;
    return result;
}

bool DataManager::saveCSV(const std::string& filename,
                          const std::vector<std::string>& headers,
                          const std::vector<std::vector<std::string>>& rows) {
    namespace fs = std::filesystem;
    
    std::string filepath = basePath + filename;
    
    // Tạo thư mục nếu chưa tồn tại
    fs::path dir = fs::path(filepath).parent_path();
    if (!dir.empty()) {
        std::error_code ec;
        fs::create_directories(dir, ec);
    }
    
    std::ofstream file(filepath);
    if (!file) {
        std::cerr << "❌ Không thể tạo file: " << filepath << std::endl;
        return false;
    }
    
    // Ghi header
    for (size_t i = 0; i < headers.size(); ++i) {
        file << headers[i];
        if (i < headers.size() - 1) file << ",";
    }
    file << "\n";
    
    // Ghi từng row
    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            // Escape dấu phẩy và dấu ngoặc kép
            std::string cell = row[i];
            bool needQuotes = (cell.find(',') != std::string::npos || 
                              cell.find('"') != std::string::npos);
            
            if (needQuotes) {
                // Escape dấu " thành ""
                std::string escaped;
                for (char c : cell) {
                    if (c == '"') escaped += "\"\"";
                    else escaped += c;
                }
                file << "\"" << escaped << "\"";
            } else {
                file << cell;
            }
            
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
    
    file.close();
    std::cout << "✅ Đã lưu " << rows.size() << " dòng vào " << filename << std::endl;
    return true;
}