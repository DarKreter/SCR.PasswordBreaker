#ifndef MD5_SCR
#define MD5_SCR

#include <list>
#include <password.hpp>
#include <string>
#include <vector>

std::string md5(std::string input);
std::string SSL_Version();

void ReadPasswords(std::string filename, std::list<Password_t>& passwd);
void ReadDictionary(std::string filename, std::vector<std::string>& dict);

#endif // MD5_SCR