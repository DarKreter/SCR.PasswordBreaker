
#include "list.hpp"
#include "threads.hpp"
#include "utils.hpp"
#include <iostream>
#include <pthread.h>
#include <tuple>

using namespace std;

int main(int argc, char* argv[])
{
    // check argc
    if(argc != 3) {
        std::cout << "Incorrect call paramters!" << std::endl;
        exit(2);
    }

    cout << "Using OpenSSL version " << pb::SSL_Version() << endl;

    // Read Dict and Passwd file
    try {
        pb::ReadDictionary(argv[1], pb::dict);
        pb::ReadPasswords(argv[2], pb::passwd);

        // for(auto& password : pb::passwd)
        //     cout << password.GetID() << " " << password.GetHash() << " " << password.GetMail()
        //          << " " << password.GetUsername() << endl;

        // for(auto& word : pb::dict)
        //     cout << word << endl;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        exit(3);
    }

    // Create threads
    pthread_t breakers[pb::MAX_THREADS_NUM];
    pthread_t listener;
    // properties of each thread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&pb::mutex, NULL);
    pthread_cond_init(&pb::condvar, NULL);

    // create threads
    pthread_create(&listener, &attr, pb::Listener, (void*)breakers);

    int thr_cnt = 0;
    // pthread_create(&breakers[thr_cnt++], &attr, pb::Breaker1, NULL);
    // pthread_create(&breakers[thr_cnt++], &attr, pb::Breaker2, NULL);
    // pthread_create(&breakers[thr_cnt++], &attr, pb::Breaker3, NULL);

    // std::string charset = "1234567890!@#$%^&*()-=_+[]{};'\\:\"|./,<>?`~";
    std::string charset = "123";
    std::vector<std::string> temp;
    std::vector<std::pair<std::string, std::string>> allComb;

    for(uint8_t i = 0; i <= 2; i++)
        pb::GenerateCombination(charset, i, temp);

    for(auto first : temp)
        for(auto second : temp)
            allComb.emplace_back(std::make_pair(first, second));
    temp.clear();

    size_t combDivide = allComb.size() / 5;
    size_t dictDivide = pb::dict.size() / 5;

    for(size_t i = 0, j = combDivide; i < allComb.size(); i += combDivide, j += combDivide) {
        if(j > allComb.size())
            j = allComb.size();
        for(size_t k = 0, l = dictDivide; k < pb::dict.size(); k += dictDivide, l += dictDivide) {
            if(l > pb::dict.size())
                l = pb::dict.size();

            pthread_create(&breakers[thr_cnt++], &attr, pb::Breaker4,
                           reinterpret_cast<void*>(
                               new pb::dataPack(pb::dict.begin() + k, pb::dict.begin() + l,
                                                allComb.begin() + i, allComb.begin() + j)));
        }
    }

    /* Wait for all threads to complete */
    for(uint8_t i = 0; i < thr_cnt; i++)
        pthread_join(breakers[i], NULL);
    pthread_cancel(listener);     // kill listener
    pthread_join(listener, NULL); // free his resources

    if(pb::passwd.length())
        cout << endl << "Breakers generated every password they could! (too bad)" << endl;
    else
        cout << endl << "Hurray! We cracked every password!" << endl;

    /* Clean up */
    pthread_attr_destroy(&attr);

    // See note in list.hpp for full meaning of this creation
    pb::passwd.JoinThreads();
    pthread_exit(NULL);
}