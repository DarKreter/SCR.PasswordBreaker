#include "threads.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <tuple>
// #include <unistd.h> //sleep

using namespace std;

namespace pb // PasswordBreaker
{

pb::SuperiorList<Password_t> passwd;
std::vector<std::string> dict;
std::queue<Password_t> threadCommQueue;
std::vector<Password_t> crackedPasswords;
pthread_mutex_t mutex;
pthread_cond_t condvar;

void Capture(int sig)
{
    switch(sig) {
    case SIGHUP:
        printf("-------------------------\n");
        printf("SIGHUP signal received!\nPrinting cracked passwords!\n");
        for(auto& psw : pb::crackedPasswords)
            cout << "Password for " << psw.GetMail() << " is " << psw.GetCrackedPassword() << endl;
        printf("-------------------------\n");
        break;
    }
}

void* Listener(void* breakers)
{
    signal(SIGHUP, Capture);
    Password_t psw;
    while(true) {
        // waiting for other threads to pass cracked passwords here via queue
        // they inform us with cond variable
        pthread_mutex_lock(&mutex);
        while(threadCommQueue.empty())
            pthread_cond_wait(&condvar, &mutex);

        // Got password
        psw = threadCommQueue.front();
        threadCommQueue.pop();
        crackedPasswords.push_back(psw);

        pthread_mutex_unlock(&mutex);

        // display information about it
        cout << "Password for " << psw.GetMail() << " is " << psw.GetCrackedPassword() << endl;

        // cracked every passowrd
        // kill breakers
        if(pb::passwd.length() == 0) {
            pthread_t* thread = (pthread_t*)breakers;
            for(int i = 0; i < MAX_THREADS_NUM; i++) {
                pthread_cancel(*thread); // kill breakers

                thread++;
            }
        }
    }
    return nullptr;
}

std::string WordMod1(std::string word)
{
    // first letter to upper
    word[0] = ::toupper(word[0]);
    return word;
}

std::string WordMod2(std::string word)
{
    // whole word upper-case
    std::transform(word.begin(), word.end(), word.begin(), ::toupper);
    return word;
}

void* Breaker1(void* data)
{
    // get dict begin dict end, comb begin comb end
    string hash, word;
    auto [dictBegin, dictEnd, combBegin, combEnd, WordMod] = *(dataPack*)data;
    delete(dataPack*)data;

    // go through combinations
    for(auto comb = combBegin; comb != combEnd; comb++) {
        auto [pre, post] = (*comb);
        // and words
        for(auto dic = dictBegin; dic != dictEnd; dic++) {
            // construct word
            word = pre + WordMod(*dic) + post;
            // and try to crack it
            BreakerCore(word, hash);
        }
    }

    pthread_exit(NULL);
}

void* Breaker2(void* data)
{
    // get dict begin dict end , comb begin comb end
    string hash, word;
    auto [dictBegin, dictEnd, combBegin, combEnd, WordMod] = *(dataPack*)data;
    delete(dataPack*)data;

    // go through each word twice to create combinations
    for(auto dic1 = dictBegin; dic1 != dictEnd; dic1++) {
        for(auto dic2 = pb::dict.begin(); dic2 != pb::dict.end(); dic2++) {
            word = (*dic1) + " " + (*dic2); // merge them
            BreakerCore(word, hash);
        }
    }
    // }

    pthread_exit(NULL);
}

void BreakerCore(std::string& word, std::string& hash)
{
    // hash word
    hash = pb::md5(word);

    // check each password
    for(auto password = passwd.begin(); password != passwd.end(); ++password) {
        if(hash == (*password).GetHash()) { // if we made it
            pb::passwd.WriteLock();
            password->Cracked(word); // marked as cracked
            pb::passwd.Unlock();
            // Send information to listener
            pthread_mutex_lock(&mutex);
            threadCommQueue.push((*password));
            pthread_mutex_unlock(&mutex);

            pb::passwd.erase(password); // remove from passwords to break

            pthread_cond_signal(&condvar);
            break;
        }
    }
}

} // namespace pb
