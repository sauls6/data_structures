#ifndef STACK_H
#define STACK_H

//Plantilla para un stack
#include "LinkedList.h"
template <class T>
class stack {
    public:
        stack(); //constructor
        ~stack(); //destructor
        bool empty() const;
        int size() const;
        T top() const;
        void push(T const &data);
        void pop();
    private:
        Node<T> *_top;
        int _size;
};

// Constructor de la pila.
// Complejidad: O(1)
template <class T>
stack<T>::stack() {
    _top = nullptr;
    _size = 0;
}

// Destructor de la pila.
// Complejidad: O(n~)
template <class T>
stack<T>::~stack() {
    while (_top != nullptr) {
        Node<T> *node = _top;
        _top = _top->getNext();
        delete node;
    }
}

// Retorna true si la pila esta vacia, false en otro caso.
// Complejidad: O(1)
template <class T>
bool stack<T>::empty() const {
    return (_size == 0);
}

// Retorna el numero de elementos en la pila.
// Complejidad: O(1)
template <class T>
int stack<T>::size() const{
    return _size;
}

// Retorna el elemento en el tope de la pila.
// Complejidad: O(1)
template <class T>
T stack<T>::top() const{
    return _top->getData();
}

// Agrega un nuevo elemento a la pila.
// Complejidad: O(1)
template <class T>
void stack<T>::push(T const &data) {
    _top = new Node<T>(data, _top);
    _size++;
}

// Elimina el elemento en el tope de la pila.
// Complejidad: O(1)
template <class T>
void stack<T>::pop() {
    if (!empty()) {
        Node<T> *node = _top;
        _top = _top->getNext();
        delete node;
        _size--;
    }
}

#endif // STACK_H