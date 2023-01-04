#ifndef LIST_HPP_SCR
#define LIST_HPP_SCR

#include <iterator>
#include <pthread.h>

namespace pb // PasswordBreaker
{

// I suggest don't create global or static variables of this class and if you do, make sure to call
// "JoinThreads()" function before main ends.
// Normally destructor will handle joining threads created by this container, but static variables
// may call destructor after mains terminates thread, so it's recommended to explicity wait for all
// threads.
template <typename T>
class SuperiorList {

#define THREAD_WAIT_BEFORE_REMOVAL 500'000 // 50ms

    // Single element of the list
    struct Node_t {
        T value;             // value
        Node_t *prev, *next; // pointers to next and previous elements (bidirectional list)

        Node_t(T _value) : value(_value) {}
    };

    size_t size;                 // size of list
    Node_t* front;               // first element
    Node_t* back;                // last element
    pthread_t lastRemovalThread; // information about last launched removal thread
    pthread_rwlock_t rw_mutex;

public:
    // classic iterator
    class Iterator {
        friend SuperiorList;
        Node_t* currentNode; // points to node
        SuperiorList* myList;

    public:
        // magic
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        Iterator(Node_t* _node, SuperiorList* spl = nullptr) : currentNode(_node), myList(spl) {}

        // dereference operators
        T operator*() const;
        T* operator->() { return &currentNode->value; }

        Iterator& operator++();   // Prefix increment
        Iterator operator++(int); // Postfix increment
        Iterator& operator--();   // Prefix decrement
        Iterator operator--(int); // Postfix decrement

        // compare operators
        bool operator==(const Iterator& a) const { return this->currentNode == a.currentNode; };
        bool operator!=(const Iterator& a) const { return this->currentNode != a.currentNode; };
    };

    // create empty list
    SuperiorList() : size(0), front(nullptr), back(nullptr), rw_mutex(PTHREAD_RWLOCK_INITIALIZER) {}
    ~SuperiorList(); // free memory

    // Waits for last thread to finish its job
    void JoinThreads();

    // size of list
    size_t length() const { return size; }

    // first and last elements
    T& Front() { return front->value; }
    T& Back() { return front->value; }

    // standard iterators
    Iterator begin() { return Iterator(front, this); }
    Iterator end() { return Iterator(nullptr, this); }
    Iterator rbegin() { return Iterator(nullptr, this); }
    Iterator rend() { return Iterator(back, this); }

    // locking functions
    void ReadLock() { pthread_rwlock_rdlock(&rw_mutex); }
    void WriteLock() { pthread_rwlock_wrlock(&rw_mutex); }
    void Unlock() { pthread_rwlock_unlock(&rw_mutex); }

    // remove single element (thread safe way)
    Iterator erase(Iterator it);

    // Adding elements
    void push_front(T _value);
    void push_back(T _value);
};

} // namespace pb

#include "list.tpp"
#endif // LIST_HPP_SCR