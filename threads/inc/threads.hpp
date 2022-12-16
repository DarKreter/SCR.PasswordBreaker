#ifndef THREADS_SCR
#define THREADS_SCR

#include "list.hpp"
#include "password.hpp"
#include <functional>
#include <list>
#include <queue>
#include <string>
#include <vector>

namespace pb // PasswordBreaker
{

extern pb::SuperiorList<Password_t> passwd;
extern std::vector<std::string> dict;
extern std::queue<Password_t> crackedPasswords;
extern pthread_mutex_t mutex;
extern pthread_cond_t condvar;

constexpr int MAX_THREADS_NUM = 100;

std::string WordMod1(std::string word);
std::string WordMod2(std::string word);

void* Listener(void*);
void BreakerCore(std::string& word, std::string& hash);

// for breaker1
struct dataPack {
#define string_vector std::vector<std::string>::iterator
#define pair_string_vector std::vector<std::pair<std::string, std::string>>::iterator
    string_vector dictBegin;
    string_vector dictEnd;
    pair_string_vector combBegin;
    pair_string_vector combEnd;
    std::function<std::string(std::string)> modification;
};

void* Breaker1(void*);
} // namespace pb

#endif // THREADS_SCR