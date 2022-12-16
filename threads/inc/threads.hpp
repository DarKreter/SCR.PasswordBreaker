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
extern std::queue<Password_t> threadCommQueue;
extern std::vector<Password_t> crackedPasswords;
extern pthread_mutex_t mutex;
extern pthread_cond_t condvar;

constexpr int MAX_THREADS_NUM = 200;

// Functions that modifies word:
//
std::string WordMod1(std::string word); // first letter upper-case
std::string WordMod2(std::string word); // whole word upper-case

// Thread waiting for cracked passwords and displaying them on the screen
void* Listener(void*);
// Core for each Breaker password
void BreakerCore(std::string& word, std::string& hash);
// thread that checks for single worded passwords with pre/post fixes
void* Breaker1(void*);
// thread that checks for double worded passwords
void* Breaker2(void*);

// data pack for passing crucial data to breakers
struct dataPack {
#define string_vector std::vector<std::string>::iterator
#define pair_string_vector std::vector<std::pair<std::string, std::string>>::iterator
    string_vector dictBegin;      // starting iterator of a dictionary
    string_vector dictEnd;        // ending iterator of a dictionary
    pair_string_vector combBegin; // starting iterator of a combination vector
    pair_string_vector combEnd;   // ending iterator of a combination vector
    // Function that modifies word before adding post/pre-fixes
    std::function<std::string(std::string)> modification;
};

} // namespace pb

#endif // THREADS_SCR