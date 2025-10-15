#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>

class CsvReader {
public:
    explicit CsvReader(const std::string& path, char sep = ',');
    ~CsvReader();
    
    std::vector<std::string> headers() const;
    bool each(std::function<void(const std::unordered_map<std::string, std::string>&)> fn);
    
    static std::string trim(const std::string& str);
    static std::string unquote(const std::string& str);
    
    bool isValid() const { return file_.is_open() && headers_loaded_; }
    std::string getError() const { return error_; }

private:
    std::ifstream file_;
    std::vector<std::string> headers_;
    char separator_;
    bool headers_loaded_;
    std::string error_;
    
    bool loadHeaders();
    std::vector<std::string> parseLine(const std::string& line);
    void skipBOM();
};