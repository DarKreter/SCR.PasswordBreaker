#include "threads.hpp"
#include "utils.hpp"
#include <iostream>
#include <pthread.h>
#include <unistd.h> //sleep

using namespace std;

namespace pb // PasswordBreaker
{

std::list<Password_t> passwd;
std::vector<std::string> dict;
pthread_mutex_t mutex;

void* Listener(void*)
{
    while(true)
        //  std::list<Password_t>::iterator
        for(auto password = passwd.begin(); password != passwd.end(); ++password) {
            // pthread_mutex_lock(&mutex);
            cout << password->GetID() << std::endl;
            // pthread_mutex_unlock(&mutex);

            sleep(1);
        }
}

/**
 * @brief
 * Just go through every word on lower-case and check them
 */
void* Breaker1(void*)
{
    string hash;
    for(const auto& word : dict) {
        sleep(1);
        hash = md5(word);
        for(auto& password : passwd) {
            if(!password.IsCracked() && hash == password.GetHash()) {
                cout << "Password for " << password.GetMail() << " is " << word << endl;
                password.Crack();
                break;
            }
        }
    }

    pthread_exit(NULL);
}

} // namespace pb
