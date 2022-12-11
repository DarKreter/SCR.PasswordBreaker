
#include "threads.hpp"
#include "utils.hpp"
#include <iostream>
#include <password.hpp>
#include <pthread.h>

using namespace std;

constexpr int THREADS_NUM = 1;

int main(int argc, char* argv[])
{
    // check argc
    if(argc != 3) {
        std::cout << "Incorrect call paramters!" << std::endl;
        exit(2);
    }

    cout << "Using OpenSSL version " << SSL_Version() << endl;

    // Read Dict and Passwd file
    try {
        ReadDictionary(argv[1], pb::dict);
        ReadPasswords(argv[2], pb::passwd);

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
    pthread_t threads[THREADS_NUM];
    // pthread_t thread;
    // properties of each thread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&pb::mutex, NULL);
    // create threads
    // pthread_create(&thread, &attr, pb::Listener, NULL);

    pthread_create(&threads[0], &attr, pb::Breaker1, NULL);

    /* Wait for all threads to complete */
    for(uint8_t i = 0; i < THREADS_NUM; i++)
        pthread_join(threads[i], NULL);

    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    return 0;
}