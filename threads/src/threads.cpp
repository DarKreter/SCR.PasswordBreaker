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
pthread_mutex_t mutex;

void* Listener(void*)
{
    int i = 0;
    while(true)
        for(auto password = passwd.begin(); password != passwd.end(); ++password) {
            if(i == 3)
                pb::passwd.erase(password);

            cout << password->GetID() << std::endl;
            usleep(10000);
            if(i++ == 10)
                return nullptr;
        }
    return nullptr;
}

/**
 * @brief
 * Just go through every word on lower-case and check them
 */
void* Breaker1(void*)
{
    // string hash;
    // for(const auto& word : pb::dict) {
    //     sleep(1);
    //     hash = pb::md5(word);
    //     for(auto password = passwd.begin(); password != passwd.end(); ++password) {
    //         if(hash == password->GetHash()) {
    //             cout << "Password for " << password->GetMail() << " is " << word << endl;
    //             pb::passwd.erase(password);
    //             break;
    //         }
    //     }
    // }

    pthread_exit(NULL);
}

} // namespace pb
