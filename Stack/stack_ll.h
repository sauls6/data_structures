#ifndef STACK_LL_H
#define STACK_LL_H

//stack implementado usando una lista encadenada
#include "LinkedList.h"
template <class T>
class stack {
    public:
        stack();
        ~stack();
        bool empty() const;
        int size() const;
        T top() const;
        void push(T const &data);
        void pop();
    private:
        LinkedList<T> stack;
};

// Constructor de la pila.
// Complejidad: O(1)
template <class T>
stack<T>::stack() {
}

// Destructor de la pila.
// Complejidad: O(1)
template <class T>
stack<T>::~stack() {
}

// Retorna true si la pila esta vacia, false en otro caso.
// Complejidad: O(1)
template <class T>
bool stack<T>::empty() const {
    return stack.isEmpty();
}

// Retorna el numero de elementos en la pila.
// Complejidad: O(1)
template <class T>
int stack<T>::size() const{
    return stack.getSize();
}

// Retorna el elemento en el tope de la pila.
// Complejidad: O(1)
template <class T>
T stack<T>::top() const{
    return stack.get(0);
}

// Agrega un nuevo elemento a la pila.
// Complejidad: O(1)
template <class T>
void stack<T>::push(T const &data) {
    stack.addFirst(data);
}

// Elimina el elemento en el tope de la pila.
// Complejidad: O(1)
template <class T>
void stack<T>::pop() {
    stack.deleteFirst();
}

#endif // STACK_H