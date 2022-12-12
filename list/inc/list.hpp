#ifndef LIST_HPP_SCR
#define LIST_HPP_SCR

#include <list>
#include <password.hpp>
#include <string>
#include <vector>

namespace pb // PasswordBreaker
{

template <typename T>
class Element_t {
    T value;
    Element_t<T>*prev, *next;

public:
    Element_t(T _value) : value(_value) {}

    Element_t<T>* Next() const { return next; }
    Element_t<T>* Prev() const { return prev; }
    void Next(Element_t<T>* el) { next = el; }
    void Prev(Element_t<T>* el) { prev = el; }

    T GetValue() { return value; }
    void SetValue(const T& _value) { value = _value; }
};

template <typename T>
class SuperiorList {
    size_t size;
    Element_t<T>* front;
    Element_t<T>* back;

public:
    SuperiorList() : size(0), front(NULL), back(NULL) {}

    size_t length() const { return size; }

    Element_t<T>* Front() { return front; }
    Element_t<T>* Back() { return back; }

    void push_front(T _value);
};

} // namespace pb

#include "list.tpp"
#endif // LIST_HPP_SCR