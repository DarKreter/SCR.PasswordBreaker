#ifndef PASSWORD_SCR
#define PASSWORD_SCR

#include <iostream>
#include <sstream>

namespace pb {

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

    inline uint16_t GetID() const { return id; }
    inline std::string GetHash() const { return md5_hash; }
    inline std::string GetMail() const { return email; }
    inline std::string GetUsername() const { return username; }
};

} // namespace pb

#endif // PASSWORD_SCR