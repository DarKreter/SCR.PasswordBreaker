
#include "threads.hpp"
#include "utils.hpp"
#include <iostream>
#include <password.hpp>
#include <pthread.h>

using namespace std;

int main(int argc, char* argv[])
{
    // check argc
    if(argc != 3) {
        std::cout << "Incorrect call paramters!" << std::endl;
        exit(2);
    }

    cout << "Using OpenSSL version " << SSL_Version() << endl;

    // Read Dict and Passwd file
    vector<Password_t> passwd;
    vector<string> dict;
    try {
        ReadDictionary(argv[1], dict);
        ReadPasswords(argv[2], passwd);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        exit(3);
    }

    // Create threads
    pthread_t threads[3];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, Foo, (void*)1);
    pthread_create(&threads[1], &attr, Foo, (void*)2);
    pthread_create(&threads[2], &attr, Foo, (void*)3);

    /* Wait for all threads to complete */
    for(int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    // for(auto& password : passwd)
    //     cout << password.GetID() << " " << password.GetHash() << " " << password.GetMail() << " "
    //          << password.GetUsername() << endl;

    // for(auto& word : dict)
    //     cout << word << endl;

    return 0;
}