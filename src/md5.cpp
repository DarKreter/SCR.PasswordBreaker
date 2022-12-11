#include "md5.hpp"
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <string>

using namespace std;

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
