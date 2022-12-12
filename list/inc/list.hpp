#ifndef LIST_HPP_SCR
#define LIST_HPP_SCR

#include <list>
#include <string>
#include <vector>

namespace pb // PasswordBreaker
{

template <typename T>
class SuperiorList {
public:
    class Element_t {
        T value;
        Element_t *prev, *next;

    public:
        Element_t(T _value) : value(_value) {}

        Element_t* Next() const { return next; }
        Element_t* Prev() const { return prev; }
        void Next(Element_t* el) { next = el; }
        void Prev(Element_t* el) { prev = el; }

        T GetValue() { return value; }
        void SetValue(const T& _value) { value = _value; }
    };

    // struct Iterator {
    //     using iterator_category = std::forward_iterator_tag;
    //     using difference_type = std::ptrdiff_t;
    //     using value_type = T;
    //     using pointer = T*;   // or also value_type*
    //     using reference = T&; // or also value_type&

    //     Iterator(pointer ptr) : m_ptr(ptr) {}

    //     reference operator*() const { return *m_ptr; }
    //     pointer operator->() { return m_ptr; }

    //     // Prefix increment
    //     Iterator& operator++()
    //     {
    //         m_ptr++;
    //         return *this;
    //     }

    //     // Postfix increment
    //     Iterator operator++(int)
    //     {
    //         Iterator tmp = *this;
    //         ++(*this);
    //         return tmp;
    //     }

    //     friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr;
    //     }; friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr !=
    //     b.m_ptr; };

    // private:
    //     pointer m_ptr;
    // };

private:
    size_t size;
    Element_t* front;
    Element_t* back;

public:
    SuperiorList() : size(0), front(NULL), back(NULL) {}

    size_t length() const { return size; }

    Element_t* Front() { return front; }
    Element_t* Back() { return back; }

    void push_front(T _value);
    void push_back(T _value);
};

} // namespace pb

#include "list.tpp"
#endif // LIST_HPP_SCR