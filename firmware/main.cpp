
#include "list.hpp"
#include "threads.hpp"
#include "utils.hpp"
#include <iostream>
#include <pthread.h>

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
    pthread_t breakers[pb::THREADS_NUM];
    pthread_t listener;
    // properties of each thread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&pb::mutex, NULL);
    pthread_cond_init(&pb::condvar, NULL);
    // create threads
    pthread_create(&listener, &attr, pb::Listener, (void*)breakers);

    pthread_create(&breakers[0], &attr, pb::Breaker1, NULL);
    pthread_create(&breakers[1], &attr, pb::Breaker2, NULL);

    /* Wait for all threads to complete */
    for(uint8_t i = 0; i < pb::THREADS_NUM; i++)
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