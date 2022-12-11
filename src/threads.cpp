#include "threads.hpp"
#include <iostream>
#include <pthread.h>

using namespace std;

#include <unistd.h> //sleep
void* Foo(void* test)
{
    sleep(1);
    cout << reinterpret_cast<long>(test) << endl;
    pthread_exit(NULL);
}