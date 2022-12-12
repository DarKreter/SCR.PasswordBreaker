#include "threads.hpp"
#include "utils.hpp"
#include <iostream>
#include <pthread.h>
#include <unistd.h> //sleep

using namespace std;

namespace pb // PasswordBreaker
{

pb::SuperiorList<Password_t> passwd;
std::vector<std::string> dict;
std::queue<Password_t> crackedPasswords;
pthread_mutex_t mutex;
pthread_cond_t condvar;

void* Listener(void*)
{
    Password_t psw;
    while(true) {
        pthread_mutex_lock(&mutex);
        while(crackedPasswords.empty())
            pthread_cond_wait(&condvar, &mutex);

        psw = crackedPasswords.front();
        crackedPasswords.pop();

        pthread_mutex_unlock(&mutex);

        cout << "Password for " << psw.GetMail() << " is " << psw.GetCrackedPassword() << endl;
    }
    return nullptr;
}

/**
 * @brief
 * Just go through every word on lower-case and check them
 */
void* Breaker1(void*)
{
    string hash;
    for(const auto& word : pb::dict) {
        // usleep(100'000);
        hash = pb::md5(word);
        for(auto password = passwd.begin(); password != passwd.end(); ++password) {
            if(hash == (*password).GetHash()) {
                pb::passwd.WriteLock();
                password->Cracked(word);
                pb::passwd.Unlock();
                // Send information to listener
                pthread_mutex_lock(&mutex);
                crackedPasswords.push((*password));
                pthread_mutex_unlock(&mutex);

                pthread_cond_signal(&condvar);

                pb::passwd.erase(password); // remove from passwords to break
                break;
            }
        }
    }

    pthread_exit(NULL);
}

} // namespace pb
