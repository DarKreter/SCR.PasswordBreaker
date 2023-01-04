#ifndef LIST_TPP_SCR
#define LIST_TPP_SCR

#include "list.hpp"
#include <pthread.h>
#include <unistd.h>	 //sleep

namespace pb  // PasswordBreaker
{

template<typename T>
void SuperiorList<T>::push_front(T _value)
{
	Node_t *temp = new Node_t(_value);
	pthread_rwlock_wrlock(&rw_mutex);  // write lock
	// empty list
	if(front == NULL) {
		front = back = temp;
		temp->next	 = nullptr;
		temp->prev	 = nullptr;
	}
	else {	// not empty
		temp->next	= front;
		temp->prev	= nullptr;
		front->prev = temp;
		front		= temp;
	}
	size++;
	pthread_rwlock_unlock(&rw_mutex);  // unlock
}

template<typename T>
void SuperiorList<T>::push_back(T _value)
{
	Node_t *temp = new Node_t(_value);

	pthread_rwlock_wrlock(&rw_mutex);  // write lock
	// empty list
	if(front == NULL) {
		front = back = temp;
		temp->next	 = nullptr;
		temp->prev	 = nullptr;
	}
	else {	// not empty list
		temp->next = nullptr;
		temp->prev = back;
		back->next = temp;
		back	   = temp;
	}
	size++;
	pthread_rwlock_unlock(&rw_mutex);  // unlock
}

template<typename T>
auto SuperiorList<T>::erase(Iterator it) -> Iterator
{
	if(it == nullptr)  // null iterator
		return nullptr;

	pthread_rwlock_wrlock(&rw_mutex);  // write lock
	// only one element in list
	if(it.currentNode->prev == nullptr && it.currentNode->next == nullptr) {
		// std::cout << "only one" << std::endl;
		front = nullptr;
		back  = nullptr;
	}
	// first element
	else if(it.currentNode->prev == nullptr) {
		// std::cout << "first element" << std::endl;
		front		= it.currentNode->next;
		front->prev = nullptr;
	}
	// last element
	else if(it.currentNode->next == nullptr) {
		// std::cout << "last element" << std::endl;
		back	   = it.currentNode->prev;
		back->next = nullptr;
	}
	// middle element
	else {
		// std::cout << "middle element" << std::endl;
		it.currentNode->next->prev = it.currentNode->prev;
		it.currentNode->prev->next = it.currentNode->next;
	}
	pthread_rwlock_unlock(&rw_mutex);  // unlock

	// This monster create thread that frees memory after 'little' delay
	// We can't remove memory instantly, because we don't know how many threads
	// are now looking at this variable. Last launched thread is stored in
	// lastRemovalThread variable If we create new thread, we just detached
	// older and write new to this variable This way JoinThreads() will only
	// wait for one that ends as last (youngest one(almost always true)) setup
	// threads as joinable
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	// lambda that frees memory
	auto Removal = [](void *node) -> void *
	{
		usleep(THREAD_WAIT_BEFORE_REMOVAL);
		if(node)
			delete reinterpret_cast<Node_t *>(node);  // free memory
		pthread_exit(NULL);
	};
	// detach older thread (if exists)
	pthread_detach(lastRemovalThread);
	// create new one
	pthread_create(&lastRemovalThread, &attr, Removal, (void *) it.currentNode);
	pthread_attr_destroy(&attr);

	// since we erase one node
	size--;

	return it.currentNode->next;
}

// Prefix increment
template<typename T>
auto SuperiorList<T>::Iterator::operator++() -> Iterator &
{
	// pthread_rwlock_rdlock(&(myList->rw_mutex)); // read lock
	currentNode = currentNode->next;
	// pthread_rwlock_unlock(&(myList->rw_mutex)); // unlock
	return *this;
}

// Postfix increment
template<typename T>
auto SuperiorList<T>::Iterator::operator++(int) -> Iterator
{
	Iterator tmp = *this;
	// pthread_rwlock_rdlock(&(myList->rw_mutex)); // read lock
	currentNode	 = currentNode->next;
	// pthread_rwlock_unlock(&(myList->rw_mutex)); // unlock
	return tmp;
}

// Prefix decrement
template<typename T>
auto SuperiorList<T>::Iterator::operator--() -> Iterator &
{
	// pthread_rwlock_rdlock(&(myList->rw_mutex)); // read lock
	currentNode = currentNode->prev;
	// pthread_rwlock_unlock(&(myList->rw_mutex)); // unlock
	return *this;
}

// Postfix decrement
template<typename T>
auto SuperiorList<T>::Iterator::operator--(int) -> Iterator
{
	Iterator tmp = *this;
	// pthread_rwlock_rdlock(&(myList->rw_mutex)); // read lock
	currentNode	 = currentNode->prev;
	// pthread_rwlock_unlock(&(myList->rw_mutex)); // unlock
	return tmp;
}

// dereference operators
template<typename T>
T SuperiorList<T>::Iterator::operator*() const
{
	pthread_rwlock_rdlock(&(myList->rw_mutex));	 // read lock
	T temp = currentNode->value;
	pthread_rwlock_unlock(&(myList->rw_mutex));	 // unlock
	return temp;
}

template<typename T>
SuperiorList<T>::~SuperiorList()
{
	pthread_join(this->lastRemovalThread, NULL);

	pthread_rwlock_destroy(&rw_mutex);

	// Clear memory
	Node_t *next, *elem = front;
	while(elem != nullptr) {
		next = elem->next;
		if(elem)
			delete elem;

		elem = next;
	}
	front = back = nullptr;
}

template<typename T>
void SuperiorList<T>::JoinThreads()
{
	usleep(2 * THREAD_WAIT_BEFORE_REMOVAL);
	pthread_join(this->lastRemovalThread, NULL);
}

}  // namespace pb

#endif	// LIST_TPP_SCR