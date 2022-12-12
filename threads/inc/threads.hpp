#ifndef THREADS_SCR
#define THREADS_SCR

#include "password.hpp"
#include <list>
#include <string>
#include <vector>

namespace pb // PasswordBreaker
{
extern std::list<Password_t> passwd;
extern std::vector<std::string> dict;
extern pthread_mutex_t mutex;

void* Listener(void*);

void* Breaker1(void*);
} // namespace pb

#endif // THREADS_SCR