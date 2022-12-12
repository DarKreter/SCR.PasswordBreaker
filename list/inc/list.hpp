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
    // Stores information about last launched removal thread
    static pthread_t lastRemovalThread;
#define THREAD_WAIT_BEFORE_REMOVAL 100'000 // 100ms

    // Single element of the list
    struct Node_t {
        T value;             // value
        Node_t *prev, *next; // pointers to next and previous elements (bidirectional list)

        Node_t(T _value) : value(_value) {}
    };

    size_t size;   // size of list
    Node_t* front; // first element
    Node_t* back;  // last element

public:
    // classic iterator
    class Iterator {
        friend SuperiorList;
        Node_t* currentNode; // points to node

    public:
        // magic
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        Iterator(Node_t* _node) : currentNode(_node) {}

        // dereference operators
        T& operator*() const { return currentNode->value; }
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
    SuperiorList() : size(0), front(nullptr), back(nullptr) {}
    ~SuperiorList(); // free memory

    // Waits for last thread to finish its job
    void JoinThreads();

    // size of list
    size_t length() const { return size; }

    // first and last elements
    T& Front() { return front->value; }
    T& Back() { return front->value; }

    // standard iterators
    Iterator begin() { return Iterator(front); }
    Iterator end() { return Iterator(nullptr); }
    Iterator rbegin() { return Iterator(nullptr); }
    Iterator rend() { return Iterator(back); }

    // remove single element (thread safe way)
    Iterator erase(Iterator it);

    // Adding elements
    void push_front(T _value);
    void push_back(T _value);
};

} // namespace pb

#include "list.tpp"
#endif // LIST_HPP_SCR