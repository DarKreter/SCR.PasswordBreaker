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

void* Listener(void*);

/**
 * @brief
 * Just go through every word on lower-case and check them
 */
void* Breaker1(void*);
/**
 * @brief
 * Go through every word on and change first letter to upper-case
 */
void* Breaker2(void*);
} // namespace pb

#endif // THREADS_SCR