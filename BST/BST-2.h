// Implementa la clase BST de Árbol Binarios de Búsqueda
// Saul Sanchez Rangel - A01373954 - TC1031 - oct/2022
#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>
#include <stack>
#include "NodeT.h"

using namespace std;

enum Traversal {preorder, inorder, postorder, levelbylevel}; // Enumeracion para el tipo de print

class BST {
    public:
        BST(); // Constructor
        ~BST(); // Destructor
        bool search(int data) const;
        void add(int data);
        void remove(int data);
        bool isEmpty() const;
        int getSize() const;

        // Act3.1
        void print(Traversal order) const;
        int height() const;
        void ancestors(int data) const;
        int whatLevelAmI(int data) const;

        // Act3.2
        int maxWidth() const;
        int nearestRelative(int data1, int data2) const;
        BST(const BST &tree);
        bool operator==(const BST &tree) const;

    private:
        NodeT *root; // Puntero a la raiz del arbol
        int size; // Numero de nodos del arbol
        
        // funciones de ayuda
        void destroynode(NodeT *node);
        int countChildren(NodeT *node) const;
        void printPreorder(NodeT *tree) const;
        void printInorder(NodeT *tree) const;
        void printPostorder(NodeT *tree) const;
        void printLevelbylevelorder(NodeT *tree) const;
        NodeT* copy(NodeT *tree) const;
        bool equals(NodeT *node1, NodeT *node2) const;
        int getHeight(NodeT *tree) const;
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
        root = new NodeT(data); // crea el nodo raíz
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
// Complejidad: O(n)
void BST::remove(int data) {
    NodeT *parent = nullptr;
    NodeT *node = root;
    // busca el nodo a eliminar
    while (node != nullptr && data != node->getData()) {
        parent = node;
        node = (data < node->getData()) ? node->getLeft() : node->getRight();
    }
    if (node == nullptr) return; // el dato no existe
    NodeT *child = nullptr;
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
            child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
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
                pred = pred->getRight();
            int predData = pred->getData();
            remove(predData);
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

// despliega los datos en el BST dependiendo del parametro order
// Complejidad: O(n)
void BST::print(Traversal order) const {
    switch (order) {
        case preorder:
            cout << "Recorrido en preorden:";
            printPreorder(root);
        break;
        case inorder:
            cout << "Recorrido en inorden:";
            printInorder(root);
        break;
        case postorder:
            cout << "Recorrido en postorden:";
            printPostorder(root);
        break;
        case levelbylevel:
            cout << "Recorrido nivel x nivel:";
            printLevelbylevelorder(root);
    }
    cout << endl;
}

// Regresa la altura del BST
// Complejidad: O(n)
// existe forma de hacerla recursiva, pero no se me ocurrio como hacerla SIN mandarle argumentos al metodo, como lo pide la especificacion
int BST::height() const {
    if (root == nullptr)
        return 0; // altura de un arbol vacio es 0
    else 
        return getHeight(root);
}

// Despliega los ancestros de un dato.
// Complejidad: O(n)
void BST::ancestors(int data) const {
    NodeT *tree = root;
        stack<NodeT*> s;
        if (data == tree->getData())
            cout << "SIN ANCESTROS"; // el dato es la raiz
        while (tree != nullptr) { // busca el dato
            s.push(tree);
            if (data == tree->getData())
                break;
            tree = (data < tree->getData()) ? tree->getLeft() : tree->getRight();
        }
        if (data == s.top()->getData()) { // el dato existe
            s.pop(); // elimina el dato para solamente desplegar los ancestros
            while (!s.empty()) { // mientras sigan habiendo ancestros
                cout << s.top()->getData() << " "; // despliega el ancestro
                s.pop(); // elimina el nodo del stack
            }
        }
        else
            cout << "DATO INEXISTENTE"; // el dato no existe
        cout << endl;
    }

// Obtiene el nivel al que se encuentra un dato.
// Complejidad: O(n) 
int BST::whatLevelAmI(int data) const {
    NodeT *tree = root;
    int level = 0;
    while (tree != nullptr) { // mientras no se llegue al final del arbol
        if (data == tree->getData()) // si se encuentra el dato
            return level;
        level++;  // si no se encuentra, se incrementa el nivel
        tree = (data < tree->getData()) ? tree->getLeft() : tree->getRight(); // se mueve a la izquierda o derecha dependiendo del dato
    }
    return -1; // el dato no existe
}

// Métodos de la actividad 3.2

// Obtiene la máxima anchura del BST.
// Complejidad: O(n)
int BST::maxWidth() const { 
    if (root == nullptr)
        return 0; // altura de un arbol vacio es 0
    queue<NodeT*> q; // cola para recorrer el arbol
    q.push(root); // inserta la raiz
    int maxNodes = 0;
    while (true) { // recorre el arbol por niveles
        int nodesInLevel = q.size(); // cantidad de nodos en el nivel actual
        if (nodesInLevel == 0)
            return maxNodes; // no hay mas nodos
        maxNodes = (nodesInLevel > maxNodes) ? nodesInLevel : maxNodes; // actualiza el maximo de nodos
        while (nodesInLevel > 0) { // recorre los nodos del nivel actual
            NodeT *node = q.front();
            q.pop();
            if (node->getLeft() != nullptr) // inserta el hijo izquierdo
                q.push(node->getLeft());
            if (node->getRight() != nullptr) // inserta el hijo derecho
                q.push(node->getRight());
            nodesInLevel--; // decrementa la cantidad de nodos en el nivel actual
        }
    }
}

// Regresa el ancestro más cercano de dos datos.
// Complejidad: O(n)
int BST::nearestRelative(int data1, int data2) const { 
    queue <NodeT*> q1;
    queue <NodeT*> q2;
    NodeT *tree = root;
    NodeT *nearestRel = root;
    if (data1 == root->getData() || data2 == root->getData()) // si alguno de los datos es la raiz
        return nearestRel->getData();
    while (tree != nullptr) { // busca el dato
        q1.push(tree);
        if (data1 == tree->getData())
            break;
        tree = (data1 < tree->getData()) ? tree->getLeft() : tree->getRight();
    }
    tree = root;
    while (tree != nullptr) { // busca el dato
        q2.push(tree);
        if (data2 == tree->getData())
            break;
        tree = (data2 < tree->getData()) ? tree->getLeft() : tree->getRight();
    }
    if (data1 == q1.back()->getData() && data2 == q2.back()->getData()) { // si ambos datos existen
        while (!q1.empty() && !q2.empty()) { // mientras sigan habiendo ancestros
            if (q1.front() == q2.front() && q1.front()->getData() != data1 && q2.front()->getData() != data2) { // si los ancestros son iguales
                nearestRel = q1.front(); // actualiza el ancestro mas cercano
                q1.pop();
                q2.pop();
            }
            else
                break;
        }
        return nearestRel->getData();
    }
    else
        return -1; // alguno de los datos no existe

    
}

// Constructor de copia de BSTs.
// Complejidad: O(n)
BST::BST(const BST &bst) {
    root = copy(bst.root);
    size = bst.size;
}

// Compara dos BSTs para verificar si son iguales.
// Complejidad: O(n)
bool BST::operator==(const BST &tree) const {
    return equals(root, tree.root);
}


// ===================FUNCIONES DE AYUDA===================

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

// Despliega los datos en preorden.
// Complejidad: O(n)
void BST::printPreorder(NodeT *tree) const{
    if (tree != nullptr) {
        cout << " " << tree->getData();
        printPreorder(tree->getLeft());
        printPreorder(tree->getRight());
    }
}

// Despliega los datos en inorden.
// Complejidad: O(n)
void BST::printInorder(NodeT *tree) const{
    if (tree != nullptr) {
        printInorder(tree->getLeft());
        cout << " " << tree->getData();
        printInorder(tree->getRight());
    }
}

// Despliega los datos en postorden.
// Complejidad: O(n)
void BST::printPostorder(NodeT *tree) const{
    if (tree != nullptr) {
        printPostorder(tree->getLeft());
        printPostorder(tree->getRight());
        cout << " " << tree->getData();
    }
}

// Despliega los datos en nivel x nivel.
// Complejidad: O(n)
void BST::printLevelbylevelorder(NodeT *tree) const{
    if (tree != nullptr) {
        queue<NodeT*> levels;
        levels.push(tree);
        while (!levels.empty()) {
            NodeT *node = levels.front();
            cout << " " << node->getData();
            if (node->getLeft() != nullptr)
                levels.push(node->getLeft());
            if (node->getRight() != nullptr)
                levels.push(node->getRight());
            levels.pop();
        }
    }
}

// Funcion auxiliar altura.
// Complejidad: O(n)
int BST::getHeight(NodeT *tree) const {
    if (tree == nullptr)
        return 0;
    int leftHeight = getHeight(tree->getLeft());
    int rightHeight = getHeight(tree->getRight());
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Copia un BST.
// Complejidad: O(n)
NodeT* BST::copy(NodeT *tree) const {
    if (tree == nullptr)
        return nullptr;
    NodeT *newNode = new NodeT(tree->getData());
    newNode->setLeft(copy(tree->getLeft()));
    newNode->setRight(copy(tree->getRight()));
    return newNode;
}

// Método auxiliar para comparar dos BSTs.
// Complejidad: O(n)
bool BST::equals(NodeT *node1, NodeT *node2) const {
    if (node1 == nullptr && node2 == nullptr)
        return true;
    if (node1 != nullptr && node2 != nullptr)
        return node1->getData() == node2->getData() && // compara los padres
               equals(node1->getLeft(), node2->getLeft()) && // compara los hijos izquierdos
               equals(node1->getRight(), node2->getRight()); // compara los hijos derechos
    return false;
}

#endif // BST_H