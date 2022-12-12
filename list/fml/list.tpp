#ifndef LIST_TPP_SCR
#define LIST_TPP_SCR

#include "list.hpp"

namespace pb // PasswordBreaker
{
template <typename T>
void SuperiorList<T>::push_front(T _value)
{
    Element_t<T>* temp = new Element_t<T>(_value);

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

} // namespace pb

#endif // LIST_TPP_SCR