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
    std::string crackedPsw;

public:
    Password_t() : id(0) {}
    explicit Password_t(std::string line)
    {
        std::stringstream ss(line);
        ss >> id >> md5_hash >> email >> std::ws;
        std::getline(ss, username);
    }

    inline uint16_t& GetID() { return id; }
    inline std::string& GetHash() { return md5_hash; }
    inline std::string& GetMail() { return email; }
    inline std::string& GetUsername() { return username; }
    inline std::string& GetCrackedPassword() { return crackedPsw; }

    inline void Cracked(const std::string& s) { crackedPsw = s; }
};

} // namespace pb

#endif // PASSWORD_SCR