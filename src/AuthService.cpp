#include "AuthService.h"
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>
#include <filesystem>

using namespace std;

AuthService::AuthService(const string& csvPath) : m_path(csvPath) {
    ensureFile();
    load();
}

void AuthService::ensureFile() {
    namespace fs = filesystem;
    fs::path p(m_path);
    fs::create_directories(p.parent_path());
    if (!fs::exists(p)) {
        ofstream f(m_path, ios::out | ios::trunc);
        // có thể ghi header nếu muốn
        // f << "username,salt,hash\n";
    }
}

static uint64_t fnv1a64(const string& s) {
    const uint64_t FNV_OFFSET = 1469598103934665603ull;
    const uint64_t FNV_PRIME  = 1099511628211ull;
    uint64_t h = FNV_OFFSET;
    for (unsigned char c : s) { h ^= c; h *= FNV_PRIME; }
    return h;
}

string AuthService::fnv1a64_hex(const string& s) {
    uint64_t x = fnv1a64(s);
    ostringstream oss; oss << hex << setw(16) << setfill('0') << x;
    return oss.str();
}

string AuthService::hashPw(const string& salt, const string& pw) {
    return fnv1a64_hex(salt + ":" + pw); // demo hash
}

string AuthService::randomSalt(size_t n) {
    static random_device rd; static mt19937_64 gen(rd());
    static const char* hexchars = "0123456789abcdef";
    uniform_int_distribution<int> dist(0,15);
    string s; s.reserve(n);
    for (size_t i=0;i<n;++i) s.push_back(hexchars[dist(gen)]);
    return s;
}

void AuthService::load() {
    m_db.clear();
    ifstream fin(m_path);
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        if (line.rfind("username",0)==0) continue; // skip header
        string u,s,h; stringstream ss(line);
        if (!getline(ss,u,',')) continue;
        if (!getline(ss,s,',')) continue;
        if (!getline(ss,h,',')) continue;
        if (!u.empty()) m_db[u] = {s,h};
    }
}

void AuthService::save() const {
    ofstream fout(m_path, ios::out|ios::trunc);
    for (auto& [u,sh] : m_db) {
        fout << u << "," << sh.first << "," << sh.second << "\n";
    }
}

bool AuthService::registerUser(const string& username, const string& password) {
    if (username.empty() || password.empty()) return false;
    if (m_db.count(username)) return false;
    string salt = randomSalt();
    string h = hashPw(salt, password);
    m_db[username] = {salt, h};
    save();
    return true;
}

bool AuthService::verify(const string& username, const string& password) const {
    auto it = m_db.find(username);
    if (it == m_db.end()) return false;
    const auto& [salt, h] = it->second;
    return hashPw(salt, password) == h;
}

void AuthService::ensureSampleUser() {
    if (!m_db.count("testuser")) {
        string salt = "abcd";
        string h = hashPw(salt, "123456"); // 9f9a27ce22a2f9c4
        m_db["testuser"] = {salt, h};
        save();
    }
}
