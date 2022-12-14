#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template <class T> // Plantilla para estructura lineal enlazada
class LinkedList {
    public:        
        LinkedList(); // constructor
        ~LinkedList(); // destructor
        void addFirst(T data); // funciones
        void addLast(T data);
        bool add(T data, int pos);
        void deleteFirst();
        void deleteLast();
        void del(int pos);
        bool isEmpty() const;
        int deleteAll();
        T set(T data, int pos);
        T get(int pos) const;
        bool change(int pos1, int pos2);
        int getSize() const;
        void print() const;
        // Metodos de Act 2.1
        void reverse();
        void shift(int n);
        bool operator==( const LinkedList<T> &list);
        // Metodos de Act 2.2
        void operator+=(LinkedList<T> const &list);
        void operator=(LinkedList<T> const &list);
        LinkedList(LinkedList<T> const &list);

    private:
        Node<T> *head;
        int size;
};

// Constructor de listas simplemente encadenadas.
// Complejidad: O(1)
template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}

// Destructor de listas simplemente encadenadas.
// Complejidad: O(n)
template <class T>
LinkedList<T>::~LinkedList() {
    deleteAll();
}

// Agrega un nuevo elemento al inicio de la lista encadenada.
// Complejidad: O(1)
template <class T>
void LinkedList<T>::addFirst(T data) {
    head = new Node<T>(data, head);
    size++;
}

// Agrega un nuevo elemento al final de la lista encadenada.
// Complejidad: O(n)
template <class T>
void LinkedList<T>::addLast(T data) {
    if (isEmpty()) // lista vacia
        addFirst(data);
    else { // contiene al menos un elemento
        Node<T> *curr = head;
        while (curr->getNext() != nullptr) // mientras no se llegue al ultimo nodo
            curr = curr->getNext(); // se avanza al siguiente nodo
        curr->setNext(new Node<T>(data)); // se agrega el nuevo nodo al final
        size++;
    }
}

// Agrega un nuevo nuevo en una posici??n dada dentro de la lista.
// Complejidad: O(n)
template <class T>
bool LinkedList<T>::add(T data, int pos) {
    if (pos > size) return false;
    else if (pos == 0)
        addFirst(data);
    else {
        Node<T> *curr = head;
        for (int i=pos; i>1; i--)
            curr = curr->getNext();
        curr->setNext(new Node<T>(data, curr->getNext()));
        size++;
    }
    return true;    
}

// Borra el primer elemento de una lista encadenada.
// Complejidad: O(1)
template <class T>
void LinkedList<T>::deleteFirst() {
    if (!isEmpty()) {
        Node<T> *temp = head;
        head = head->getNext();
        delete temp;
        size--;
    }
}

// Borra el ??ltimo elemento de la lista encadenada.
// Complejidad: O(n)
template <class T>
void LinkedList<T>::deleteLast() {
        if (head->getNext() == nullptr) // solo un elemento
            deleteFirst();
        else {
            Node<T> *curr = head;
            while (curr->getNext()->getNext() != nullptr)
                curr = curr->getNext();
            delete curr->getNext();
            curr->setNext(nullptr);
            size--;
        }
}

// Borra el elemento en una posici??n v??lida.
// Complejidad: O(n)
template <class T>
void LinkedList<T>::del(int pos) {
    if (pos == 0)
        deleteFirst();
    else if (pos == size - 1)
        deleteLast();
    else {
        Node<T> *ptr = head;
        for (int i=1; i<pos; i++)
            ptr = ptr->getNext();
        Node<T> *nodo = ptr->getNext(); // nodo a borrar
        ptr->setNext(nodo->getNext());
        delete nodo;
        size--;
    }
}

// Verifica si la lista est?? vac??a.
// Complejidad: O(1)
template <class T>
bool LinkedList<T>::isEmpty() const {
    return (size == 0);
}

// Elimina todos los elementos de una lista encadenada.
// Complejidad: O(n)
template <class T>
int LinkedList<T>::deleteAll() {
    int deleted = 0;
    while (!isEmpty()) {
        deleteFirst();
        deleted++;
    }
    return deleted;
}

// Modifica la informaci??n del nodo en la posici??n v??lida dada en la lista encadenada
// Complejidad: O(n)
template <class T>
T LinkedList<T>::set(T data, int pos) {
    Node<T> *ptr = head;
    for (int i=0; i<pos; i++)
        ptr = ptr->getNext();
    T temp = ptr->getData();
    ptr->setData(data);
    return temp;
}

// Obtiene la informaci??n de una posici??n v??lida dada en la lista encadenada
// Complejidad: O(n)
template <class T>
T LinkedList<T>::get(int pos) const {
        Node<T> *ptr = head;
        for (int i=0; i<pos; i++) //me muevo hasta la posicion
            ptr = ptr->getNext();
        return ptr->getData(); //regreso el valor
}

// Intercambia informaci??n entre dos posiciones de la lista encadenada.
// Regresa false si alguna posici??n no es v??lida.
// Complejidad: O(n)
template <class T>
bool LinkedList<T>::change(int pos1, int pos2) {
    if (pos1 <= 0 || pos2 < 0 || pos1 >= size || pos2 >= size)
        return false;
    if (pos1 != pos2) {
        // localizar la pos1
        Node<T> *ptr1 = head;
        for (int i=0; i<pos1; i++)
            ptr1 = ptr1->getNext();
        // localizar la pos2
        Node<T> *ptr2 = head;
        for (int i=0; i<pos2; i++)
            ptr2 = ptr2->getNext();
        // intercambiar los datos
        T temp = ptr1->getData();
        ptr1->setData(ptr2->getData());
        ptr2->setData(temp);
    }
    return true; // asumo que  es valido que pos1 == pos2
}

// Obtiene el tama??o de la lista encadenada, el numero de nodos.
// Complejidad: O(1)
template <class T>
int LinkedList<T>::getSize() const {
    return size;
}

// Despliega el contenido de la lista encadenada
// Complejidad: O(n)
template <class T>
void LinkedList<T>::print() const{
    if (!isEmpty()) {
    cout << head->getData();
    Node<T> *curr = head->getNext();
        while (curr != nullptr) {
            cout << " " << curr->getData();
            curr = curr->getNext();
        }
    }
}

// Invierte el contenido de la lista encadenada.
// Complejidad: O(n)
template <class T>
void LinkedList<T>::reverse() {
    Node<T> *prev = nullptr;
    Node<T> *curr = head;
    Node<T> *next = nullptr;
    while (curr != nullptr) {
        next = curr->getNext();
        curr->setNext(prev);
        prev = curr;
        curr = next;
    }
    head = prev;
}

// Realiza el corrimiento de n casillas en la lista encadenada.
// Complejidad: O(n)
template <class T>
void LinkedList<T>::shift(int n) {
    if (n < 0)
        n = size + n;
    if (n > 0 && n < size) {
        Node<T> *ptr = head;
        for (int i=0; i<n-1; i++)
            ptr = ptr->getNext();
        Node<T> *temp = head;
        head = ptr->getNext();
        ptr->setNext(nullptr);
        ptr = head;
        while (ptr->getNext() != nullptr)
            ptr = ptr->getNext();
        ptr->setNext(temp);
    }
}
// el de shift -1 es igual a 3 
// con los negativos es -n+size

// Verifica si dos listas encadenadas son id??nticas.
// Complejidad:
template <class T>
bool LinkedList<T>::operator==(const LinkedList<T> &list) {
    if (size != list.size)
        return false;
    else {
        Node<T> *ptr1 = head;
        Node<T> *ptr2 = list.head;
        while (ptr1 != nullptr) {
            if (ptr1->getData() != ptr2->getData())
                return false;
            ptr1 = ptr1->getNext();
            ptr2 = ptr2->getNext();
        }
        return true;
    }
}

#endif // LINKEDLIST_H