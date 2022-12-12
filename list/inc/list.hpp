#ifndef LIST_HPP_SCR
#define LIST_HPP_SCR

#include <list>
#include <string>
#include <vector>

namespace pb // PasswordBreaker
{

template <typename T>
class SuperiorList {
    struct Node_t {
        T value;
        Node_t *prev, *next;

        Node_t(T _value) : value(_value) {}
    };

    size_t size;
    Node_t* front;
    Node_t* back;

public:
    class Iterator {
    public: // TODO: remove this
        friend SuperiorList;
        Node_t* currentNode;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        Iterator(Node_t* _node) : currentNode(_node) {}
        // Iterator() noexcept : m_pCurrentNode(m_spRoot) {}

        T& operator*() const { return currentNode->value; }
        T* operator->() { return &currentNode->value; } // ???

        Iterator& operator++();   // Prefix increment
        Iterator operator++(int); // Postfix increment
        Iterator& operator--();   // Prefix decrement
        Iterator operator--(int); // Postfix decrement

        bool operator==(const Iterator& a) const { return this->currentNode == a.currentNode; };
        bool operator!=(const Iterator& a) const { return this->currentNode != a.currentNode; };
    };

    SuperiorList() : size(0), front(nullptr), back(nullptr) {}
    ~SuperiorList();

    size_t length() const { return size; }

    T& Front() { return front->value; }
    T& Back() { return front->value; }

    Iterator begin() { return Iterator(front); }
    Iterator end() { return Iterator(nullptr); }
    Iterator rbegin() { return Iterator(nullptr); }
    Iterator rend() { return Iterator(back); }

    Iterator erase(Iterator it);

    void push_front(T _value);
    void push_back(T _value);
};

} // namespace pb

#include "list.tpp"
#endif // LIST_HPP_SCR