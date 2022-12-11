#ifndef PASSWORD_SCR
#define PASSWORD_SCR

#include <iostream>
#include <sstream>

class Password_t {
    uint16_t id;
    std::string md5_hash;
    std::string email;
    std::string username;

public:
    explicit Password_t(std::string line)
    {
        std::stringstream ss(line);
        ss >> id >> md5_hash >> email >> std::ws;
        std::getline(ss, username);
    }

    inline uint16_t GetID() { return id; }
    inline std::string GetHash() { return md5_hash; }
    inline std::string GetMail() { return email; }
    inline std::string GetUsername() { return username; }
};

#endif // PASSWORD_SCR