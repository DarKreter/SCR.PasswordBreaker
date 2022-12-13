#ifndef THREADS_SCR
#define THREADS_SCR

#include "list.hpp"
#include "password.hpp"
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

constexpr int THREADS_NUM = 3;

void* Listener(void*);
void BreakerCore(std::string& word, std::string& hash);

void* Breaker1(void*); // normal words
void* Breaker2(void*); // first letter upper-case
void* Breaker3(void*); // whole word upper-case
} // namespace pb

#endif // THREADS_SCR