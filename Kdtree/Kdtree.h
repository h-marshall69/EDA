#ifndef KDTREE_H_
#define KDTREE_H_
#include <vector>

bool operator==(const std::vector<int>& left, const std::vector<int>& right) {
    if(left.size() != right.size())
        return false;

    for(int i = 0; i < left.size(); i++) {
        if(left[i] != right[i])
            return false;
    }
    return true;
}

class Knode {
public:
    std::vector<int> dim;
    int nivel;
    Knode *left;
    Knode *right;
    Knode() {
        nivel = 0;
        left = NULL;
        right = NULL;
    }
    Knode (std::vector<int> d) {
        dim = d;
        nivel = 0;
        left = NULL;
        right = NULL;
    }
};

class Kdtree {
private:
    void insertar(Knode *&current, std::vector<int> dim, int n) {
        if(current == NULL) {
            Knode *new_knode = new Knode(dim);
            new_knode->nivel = n;
            current = new_knode;
        }
        else {
            if(dim[n] < current->dim[n]) {
                //std::cout << "left: " << current->dim[0] << " < " << dim[0] << std::endl;
                if(n + 1 == dim.size())
                    n = -1;
                insertar(current->left, dim, n + 1);
            }
            else{
                //std::cout << "right: " << current->dim[0] << " > " << dim[0] << std::endl;
                if(n + 1 == dim.size())
                    n = -1;
                insertar(current->right, dim, n + 1);
            }
        }
    }
    Knode *buscar(Knode *, std::vector<int> dim);
public:
    Knode *root;
    Kdtree() {
        root = NULL;
    }
    void insertar(std::vector<int> dim) {insertar(root, dim, 0);}
    Knode *buscar(std::vector<int> dim) {buscar(root, dim);}
    void prueba(std::vector<int> dim) {
        Knode *tm = buscar(dim);
        std::cout << buscar(dim)->nivel;
    }
};

Knode* Kdtree::buscar(Knode *current, std::vector<int> dim) {
    if(current != NULL) {
        int n = current->nivel % dim.size();
        if(current->dim == dim) {
            //std::cout << current->nivel << std::endl;
            return current;
        }
        else {
            if(current->dim[n] > dim[n])
                return buscar(current->left, dim);
            else
                return buscar(current->right, dim);
        }
    }
    return NULL;
}
#endif // KDTREE_H_