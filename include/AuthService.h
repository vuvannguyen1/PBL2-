#pragma once
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

class AuthService {
public:
    explicit AuthService(const string&);

    // tạo file & thư mục nếu chưa có
    void ensureFile();

    // đăng ký: false nếu username đã tồn tại hoặc rỗng
    bool registerUser(const string&, const string&);

    // xác thực đăng nhập
    bool verify(const string&, const string&) const;

    // tạo sẵn user mẫu testuser/123456 nếu chưa có
    void ensureSampleUser();

private:
    string m_path;
    // username -> (salt, hash)
    unordered_map<string, pair<string, string>> m_db;

    void load();
    void save() const;

    static string randomSalt(size_t n = 16);
    static string hashPw(const string&, const string&);
    static string fnv1a64_hex(const string&);
};
