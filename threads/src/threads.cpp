#include "threads.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <tuple>
// #include <unistd.h> //sleep

using namespace std;

namespace pb // PasswordBreaker
{

pb::SuperiorList<Password_t> passwd;
std::vector<std::string> dict;
std::queue<Password_t> crackedPasswords;
pthread_mutex_t mutex;
pthread_cond_t condvar;

void* Listener(void* breakers)
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

        // cracked every passowrd
        // kill breakers
        if(pb::passwd.length() == 0) {
            pthread_t* thread = (pthread_t*)breakers;
            for(int i = 0; i < MAX_THREADS_NUM; i++) {
                pthread_cancel(*thread); // kill listener

                thread++;
            }
        }
    }
    return nullptr;
}

std::string WordMod1(std::string word)
{
    word[0] = ::toupper(word[0]);
    return word;
}

std::string WordMod2(std::string word)
{
    std::transform(word.begin(), word.end(), word.begin(), ::toupper);
    return word;
}

/**
 * @brief
 * Full upper-case
 */
void* Breaker1(void* data)
{
    // get dict begin dict end , comb begin comb end
    string hash, word;
    auto [dictBegin, dictEnd, combBegin, combEnd, WordMod] = *(dataPack*)data;
    delete(dataPack*)data;

    for(auto comb = combBegin; comb != combEnd; comb++) {
        auto [pre, post] = (*comb);
        for(auto dic = dictBegin; dic != dictEnd; dic++) {
            word = pre + WordMod(*dic) + post;
            BreakerCore(word, hash);
        }
    }

    pthread_exit(NULL);
}

void BreakerCore(std::string& word, std::string& hash)
{
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

            pb::passwd.erase(password); // remove from passwords to break

            pthread_cond_signal(&condvar);
            break;
        }
    }
}

} // namespace pb
