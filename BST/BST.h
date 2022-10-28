// Implementa la clase BST de Árbol Binarios de Búsqueda
#ifndef BST_H
#define BST_H

#include "NodeT.h"

class BST {
    public:
        BST();
        ~BST();
        bool search(int data) const;
        void add(int data);
        void remove(int data);
        bool isEmpty() const;
        int getSize() const;
        void print() const;

    private:
        NodeT *root;
        int size;
        // funciones de ayuda
        void destroynode(NodeT *node);
        int countChildren(NodeT *node) const;
};

// Constructor del árbol
// Complejidad: O(1)
BST::BST() {
    root = nullptr;
    size = 0;
}

// Destructor del árbol
// Complejidad: O(n)
BST::~BST() {
    destroynode(root);
}

// Busca un dato dentro del BST
// Complejidad: O(altura(BST))
bool BST::search(int data) const {
    NodeT *node = root;
    while (node != nullptr) {
        // checar si el dato está en la raíz
        if (data == node->getData()) // lo encontró
            return true;
        // buscar en el subárbol adecuado
        node = (data < node->getData()) ? node->getLeft() : node->getRight();
        }
    return false;
}

// Agrega un nuevo dato dentro del árbol
// Complejidad: O(altura(BST))
void BST::add(int data) {
    if (root == nullptr)
        root = new NodeT(data);
    else {
        NodeT *parent = nullptr;
        NodeT *node = root;
        // busca el nodo padre del nuevo nodo
        while (node != nullptr) {
            if (data == node->getData()) // el dato ya existe
                return;
            parent = node;
            // busca en el subárbol correspondiente
            node = (data < node->getData()) ? node->getLeft() : node->getRight();
        }
        // agrega el nuevo elemento
        if (data < parent->getData())
            parent->setLeft(new NodeT(data));
        else
            parent->setRight(new NodeT(data));
    }
    size++;
}

// Elimina un dato del BST.
// Complejidad: O()
void BST::remove(int data) {
    NodeT *parent = nullptr;
    NodeT *node = root;
    // busca el nodo a eliminar
    while (node != nullptr && data != node->getData()) {
        parent = node;
        node = (data < node->getData()) ? node->getLeft() : node->getRight();
    }
    if (node == nullptr) return; // el dato no existe
    switch (countChildren(node)) {
        case 0:
            if (parent == nullptr) { // eliminar el único nodo en BST
                root = nullptr;
            }
            else {
                if (data < parent->getData())
                    parent->setLeft(nullptr);
                else
                    parent->setRight(nullptr);
            }
            delete node;
            size--;
        break;
        case 1:
            NodeT *child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
            if (parent == nullptr) { // eliminar la raíz del BST
                root = child;
            }
            else {
                if (data < parent->getData())
                    parent->setLeft(child);
                else
                    parent->setRight(child);
            }
            delete node;
            size--;
        break;
        default: // 2 hijos
            //encontrar predecesor
            NodeT *pred = node->getLeft();
            while (pred->getRight() != nullptr)
                pred == pred->getRight();
            int predData = pred->getData();
            remove(pred->getData());
            node->setData(predData);
        break;
    }

}

// verifica si el BST está vacío
// Complejidad: O(1)
bool BST::isEmpty() const {
    return size == 0;
}

// Obtiene la cantidad de nodos en el BST.
// Complejidad: O(1)
int BST::getSize() const {
    return size;
}

// despliega los datos en el BST
// Complejidad: O()
void BST::print() const {
    
} 

// FUNCIONES DE AYUDA

// Borra todos los nodos de un BST.
// Complejidad: O(n)
void BST::destroynode(NodeT *root) {
    if (root != nullptr) {
        destroynode(root->getLeft());
        destroynode(root->getRight());
        delete root;
        root = nullptr;
    }
}

// Cuenta la cantidad de hijos de un nodo.
// Complejidad: O(1)
int BST::countChildren(NodeT *node) const {
    int count = 0;
    if (node->getLeft() != nullptr)
        count++;
    if (node->getRight() != nullptr)
        count++;
    return count;
}

#endif // BST_H