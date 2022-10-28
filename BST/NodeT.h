// Definición de los nodos para árboles binarios
#ifndef NODET_H
#define NODET_H

class NodeT {
    public:
        NodeT(int data, NodeT *left = nullptr, NodeT *right = nullptr);
        int getData();
        NodeT *getLeft();
        NodeT *getRight();
        void setData(int data);
        void setLeft(NodeT *left);
        void setRight(NodeT *right);

    private:
        int data;
        NodeT *left, *right;
};

// Constructor de nodos de un árbol binario
NodeT::NodeT(int data, NodeT *left, NodeT *right) {
    this->data = data;
    this->left = left; 
    this->right = right;
}

// Obtiene el dato de un nodo
int NodeT::getData() { 
    return data; 
}

// Obtiene el apuntador al subárbol izquierdo
NodeT *NodeT::getLeft() { 
    return left; 
}

// Obtiene el apuntador al subárbol derecho
NodeT *NodeT::getRight() { 
    return right; 
}

// Modifica el dato del nodo
void NodeT::setData(int data) {
    this->data = data;
}

// modifica el apuntador al subárbol izquierdo
void NodeT::setLeft(NodeT *left) {
    this->left = left;
}

// modifica el apuntador al subárbol derecho
void NodeT::setRight(NodeT *right) {
    this->right = right;
}

#endif // NODET_H