#ifndef MD5_SCR
#define MD5_SCR

#include "list.hpp"
#include "password.hpp"
#include <list>
#include <string>
#include <vector>

namespace pb {

// hash word with md5 algorithm
std::string md5(const std::string& input);
// check openSSL lib ver
std::string SSL_Version();

// Read passwords from file
void ReadPasswords(std::string filename, pb::SuperiorList<Password_t>& passwd);
// read words from dictionary
void ReadDictionary(std::string filename, std::vector<std::string>& dict);

// Generate all combinations from charset, to vector
void GenerateCombination(std::string, uint8_t, std::vector<std::string>&, std::string = "");

} // namespace pb

#endif // MD5_SCR