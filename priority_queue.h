#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
using namespace std;

template <class T>
class priority_queue {
    public:
        priority_queue();
        void push(T const &data);
        void pop();
        T top() const;
        bool empty() const;
        int size() const;

    private:
        vector<T> queue;
        // Funciones auxiliares
        void rearrange_down(int pos);
        void rearrange_up(int pos);
};

// Constructor: Crea una fila priorizada
// Complejidad: O(1)
template <class T>
priority_queue<T>::priority_queue() {
    queue.push_back(T()); 
}

// Agregue un dato a la fila priorizada.
// Complejidad O(log n)
template <class T>
void priority_queue<T>::push(T const &data) {
    queue.push_back(data);
    rearrange_up(size());
}

// Saca de la fila priorizada el dato que tiene mayor prioridad.
// Complejidad O(log n)
template <class T>
void priority_queue<T>::pop() {
    if (size() == 1) 
        queue.pop_back();
    else {
        queue[1] = queue[size()]; // Copio el ultimo elemento en la raiz
        queue.pop_back(); // Elimino el ultimo elemento
        rearrange_down(1);
    }
}

// Regresa el valor del dato que esta con mayor prioridad en la fila priorizada.
// Complejidad O(1)
template <class T>
T priority_queue<T>::top() const {
    return queue[1];  // el dato con mayor prioridad está en la posicion 1
}

// Regresa un valor booleano diciendo si la fila  priorizada está vacía o tiene datos.
// Complejidad O(1)
template <class T>
bool priority_queue<T>::empty() const {
    return queue.size() == 1;
}

// Regresa la cantidad de datos que tiene la fila priorizada
// Complejidad O(1)
template <class T>
int priority_queue<T>::size() const {
    return queue.size() - 1;
}

// Funciones auxiliares

// Ordena hacia abajo el elemento en una posicion de la fila priorizada
// Complejidad O(log n)
template <class T>
void priority_queue<T>::rearrange_down(int pos) {
    int n = size();
    int left = 2 * pos;
    if (left > n) return; // no tiene hijos
    int max = left;
    // checo el hijo derecho
    int right = left + 1;
    if (right <= n && queue[right].ip > queue[left].ip)
        max = right;
    // checo si requiero intercambiar
    if (queue[max].ip > queue[pos].ip) {
        swap(queue[max], queue[pos]);
        rearrange_down(max);
    }
}

// Ordena hacia arriba el elemento en una posicion de la fila priorizada
// Complejidad O(log n)
template <class T>
void priority_queue<T>::rearrange_up(int pos) {
    if (pos == 1) return; // ya llegue a la raiz
    int parent = pos / 2;
    if (queue[pos].ip > queue[parent].ip) {
        swap(queue[parent], queue[pos]);
        rearrange_up(parent);
    }
}

#endif // PRIORITYQUEUE.H