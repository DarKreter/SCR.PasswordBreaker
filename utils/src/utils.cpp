#include "utils.hpp"
#include <fstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <string>

using namespace std;

namespace pb {

void ReadPasswords(std::string filename, pb::SuperiorList<Password_t>& passwd)
{
    ifstream file(filename);
    if(!file.is_open())
        throw runtime_error("Cannot open file " + filename);

    string line;
    while(getline(file, line))
        if(line != "")
            passwd.push_back(
                std::move(Password_t(line))); // password_t has intelligent constructor that handles
                                              // parsing this raw  line from file

    file.close();

    return;
}

void ReadDictionary(std::string filename, std::vector<std::string>& dict)
{
    ifstream file(filename);
    if(!file.is_open())
        throw runtime_error("Cannot open file " + filename);

    string line;
    while(getline(file, line))
        if(line != "")
            dict.push_back(std::move(line)); // just put words in vector
    file.close();
}

void GenerateCombination(string set, uint8_t k, std::vector<std::string>& allComb, string prefix)
{
    if(!k) {
        allComb.emplace_back(prefix);
        return;
    }

    for(size_t i = 0; i < set.length(); i++) {
        string newPrefix;
        newPrefix = prefix + set[i];
        GenerateCombination(set, k - 1, allComb, newPrefix);
    }
}

string md5(const string& input)
{
    std::stringstream result;

    unsigned char digest[MD5_DIGEST_LENGTH];

    MD5((unsigned char*)input.c_str(), input.length(), digest);

    // change to prettier form
    for(int i = 0; i < 16; ++i)
        result << std::hex << setfill('0') << setw(2) << (int)digest[i];

    return result.str();
}

std::string SSL_Version() { return SSLeay_version(SSLEAY_VERSION); }

} // namespace pb