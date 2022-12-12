#ifndef LIST_TPP_SCR
#define LIST_TPP_SCR

#include "list.hpp"

namespace pb // PasswordBreaker
{
template <typename T>
void SuperiorList<T>::push_front(T _value)
{
    Element_t* temp = new Element_t(_value);

    if(front == NULL) {
        front = back = temp;
        temp->Next(NULL);
        temp->Prev(NULL);
    }
    else {
        temp->Next(front);
        temp->Prev(NULL);
        front->Prev(temp);
        front = temp;
    }
}

template <typename T>
void SuperiorList<T>::push_back(T _value)
{
    Element_t* temp = new Element_t(_value);

    if(front == NULL) {
        front = back = temp;
        temp->Next(NULL);
        temp->Prev(NULL);
    }
    else {
        temp->Next(NULL);
        temp->Prev(back);
        back->Next(temp);
        back = temp;
    }
}

} // namespace pb

#endif // LIST_TPP_SCR