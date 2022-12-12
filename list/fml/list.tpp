#ifndef LIST_TPP_SCR
#define LIST_TPP_SCR

#include "list.hpp"
#include <pthread.h>
#include <time.h>

#include <iostream> //TODO: remove this

namespace pb // PasswordBreaker
{
template <typename T>
void SuperiorList<T>::push_front(T _value)
{
    Node_t* temp = new Node_t(_value);

    if(front == NULL) {
        front = back = temp;
        temp->next = nullptr;
        temp->prev = nullptr;
    }
    else {
        temp->next = front;
        temp->prev = nullptr;
        front->prev = temp;
        front = temp;
    }
    size++;
}

template <typename T>
void SuperiorList<T>::push_back(T _value)
{
    Node_t* temp = new Node_t(_value);

    if(front == NULL) {
        front = back = temp;
        temp->next = nullptr;
        temp->prev = nullptr;
    }
    else {
        temp->next = nullptr;
        temp->prev = back;
        back->next = temp;
        back = temp;
    }
    size++;
}

template <typename T>
auto SuperiorList<T>::erase(Iterator it) -> Iterator
{
    if(it == nullptr) // null iterator
        return nullptr;

    // only one element in list
    if(it.currentNode->prev == nullptr && it.currentNode->next == nullptr) {
        // std::cout << "only one" << std::endl;
        front = nullptr;
        back = nullptr;
    }
    // first element
    else if(it.currentNode->prev == nullptr) {
        // std::cout << "first element" << std::endl;
        front = it.currentNode->next;
        front->prev = nullptr;
    }
    // last element
    else if(it.currentNode->next == nullptr) {
        // std::cout << "last element" << std::endl;
        back = it.currentNode->prev;
        back->next = nullptr;
    }
    // middle element
    else {
        // std::cout << "middle element" << std::endl;
        it.currentNode->next->prev = it.currentNode->prev;
        it.currentNode->prev->next = it.currentNode->next;
    }

    // run thread that frees memory after little delay
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    auto Removal = [](void* node) -> void* {
        struct timespec request = {0, 50'000'000};

        nanosleep(&request, NULL);
        delete reinterpret_cast<Node_t*>(node);
        pthread_exit(NULL);
    };
    pthread_create(&thread, &attr, Removal, (void*)it.currentNode);
    int err = pthread_detach(thread);
    std::cout << "err: " << err << std::endl;
    pthread_attr_destroy(&attr);

    size--;

    return it.currentNode->next;
}

// Prefix increment
template <typename T>
auto SuperiorList<T>::Iterator::operator++() -> Iterator&
{
    currentNode = currentNode->next;
    return *this;
}

// Postfix increment
template <typename T>
auto SuperiorList<T>::Iterator::operator++(int) -> Iterator
{
    Iterator tmp = *this;
    currentNode = currentNode->next;
    return tmp;
}

// Prefix decrement
template <typename T>
auto SuperiorList<T>::Iterator::operator--() -> Iterator&
{
    currentNode = currentNode->prev;
    return *this;
}

// Postfix decrement
template <typename T>
auto SuperiorList<T>::Iterator::operator--(int) -> Iterator
{
    Iterator tmp = *this;
    currentNode = currentNode->prev;
    return tmp;
}

template <typename T>
SuperiorList<T>::~SuperiorList()
{
    Node_t *next, *elem = front;
    while(elem != nullptr) {
        next = elem->next;
        delete elem;

        elem = next;
    }
}

} // namespace pb

#endif // LIST_TPP_SCR