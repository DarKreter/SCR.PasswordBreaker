#ifndef MD5_SCR
#define MD5_SCR

#include "list.hpp"
#include "password.hpp"
#include <list>
#include <string>
#include <vector>

namespace pb {

std::string md5(const std::string& input);
std::string SSL_Version();

void ReadPasswords(std::string filename, pb::SuperiorList<Password_t>& passwd);
void ReadDictionary(std::string filename, std::vector<std::string>& dict);

void GenerateCombination(std::string, uint8_t, std::vector<std::string>&, std::string = "");

} // namespace pb

#endif // MD5_SCR