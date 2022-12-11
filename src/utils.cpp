#include "utils.hpp"
#include <fstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <string>

using namespace std;

void ReadPasswords(std::string filename, std::vector<Password_t>& passwd)
{
    ifstream file(filename);
    if(!file.is_open())
        throw runtime_error("Cannot open file " + filename);

    string line;
    while(getline(file, line))
        if(line != "")
            passwd.push_back(std::move(Password_t(line)));
    file.close();
}

void ReadDictionary(std::string filename, std::vector<std::string>& dict)
{
    ifstream file(filename);
    if(!file.is_open())
        throw runtime_error("Cannot open file " + filename);

    string line;
    while(getline(file, line))
        if(line != "")
            dict.push_back(std::move(line));
    file.close();
}

string md5(string input)
{
    std::stringstream result;

    unsigned char digest[MD5_DIGEST_LENGTH];

    MD5((unsigned char*)input.c_str(), input.length(), digest);

    for(int i = 0; i < 16; ++i)
        result << std::hex << setfill('0') << setw(2) << (int)digest[i];

    return result.str();
}

std::string SSL_Version() { return SSLeay_version(SSLEAY_VERSION); }
