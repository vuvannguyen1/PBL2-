#pragma once
#include <string>
#include <unordered_map>

struct Movie {
    std::string id;
    std::string slug;
    std::string title;
    std::string age_rating;
    std::string country;
    std::string language;
    std::string genres;
    std::string duration;
    std::string release_date;
    std::string director;
    std::string cast;
    std::string description;
    std::string poster_path;
    std::string status;
    
    // Generate slug from title for lookup
    static std::string generateSlug(const std::string& title);
};

class MovieRepo {
public:
    MovieRepo() = default;
    
    bool loadFromCsv(const std::string& path);
    const Movie* findById(const std::string& id) const;
    const Movie* findBySlug(const std::string& slug) const;
    
    size_t size() const { return movies_by_id_.size(); }
    std::string getError() const { return error_; }
    
    // For debugging/testing
    void printAll() const;

private:
    std::unordered_map<std::string, Movie> movies_by_id_;
    std::unordered_map<std::string, Movie> movies_by_slug_;
    std::string error_;
};