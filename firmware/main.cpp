
#include "list.hpp"
#include "threads.hpp"
#include "utils.hpp"
#include <iostream>
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
    pthread_t threads[THREADS_NUM];
    pthread_t thread;
    // properties of each thread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&pb::mutex, NULL);
    // create threads
    pthread_create(&thread, &attr, pb::Listener, NULL);

    pthread_create(&threads[0], &attr, pb::Breaker1, NULL);

    /* Wait for all threads to complete */
    for(uint8_t i = 0; i < THREADS_NUM; i++)
        pthread_join(threads[i], NULL);
    pthread_join(thread, NULL);

    /* Clean up */
    pthread_attr_destroy(&attr);

    // See note in list.hpp for full meaning of this creation
    pb::passwd.JoinThreads();
    pthread_exit(NULL);
}