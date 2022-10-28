#ifndef QUEUE_H
#define QUEUE_H

//Plantilla para un queue
#include "Node.h"
template <class T>
class queue {
    public:
        queue();
        ~queue();
        bool empty() const;
        int size() const;
        T front() const;
        void push(T const &data);
        void pop();
    private:
        Node <T> *tail;
        int _size;
};

// Constructor de la fila.
// Complejidad: O(1)
template <class T>
queue<T>::queue() {
    tail = nullptr;
    _size = 0;
}

// Destructor de la pila.
// Complejidad: O(1)
template <class T>
queue<T>::~queue() {
    if (!empty()) {
        // convertir a una lista lineal
        Node <T> *head = tail->getNext();
        tail->setNext(nullptr);
        // borrar los elementos como si fuera una lista lineal
        while (head != nullptr) {
            Node <T> *node = head;
            head = head->getNext();
            delete node;
        }
    }
}

// Retorna true si la pila esta vacia, false en otro caso.
// Complejidad: O(1)
template <class T>
bool queue<T>::empty() const {
    return (_size == 0);
}

// Retorna el numero de elementos en la pila.
// Complejidad: O(1)
template <class T>
int queue<T>::size() const{
    return _size;
}

// Retorna el elemento en el tope de la pila.
// Complejidad: O(1)
template <class T>
T queue<T>::front() const{
    return tail->getNext()->getData();
}

// Agrega un nuevo elemento a la pila.
// Complejidad: O(1)
template <class T>
void queue<T>::push(T const &data) {
    Node<T> *node = new Node<T>(data);
    if (empty()) {
        node->setNext(node);
    }
    else {
        node->setNext(tail->getNext());
        tail->setNext(node);
    }
    tail = node;
    _size++;
}

// Elimina el elemento en el tope de la pila.
// Complejidad: O(1)
template <class T>
void queue<T>::pop() {
    if (!empty()) {
        Node<T> *front = tail->getNext();
        if (front == tail)
            tail = nullptr;
        else
            tail->setNext(front->getNext());
        delete front;
        _size--;
    }
}

#endif // STACK_H