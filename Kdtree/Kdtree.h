#ifndef KDTREE_H_
#define KDTREE_H_
#include <vector>
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
public:
    Knode *root;
    Kdtree() {
        root = NULL;
    }
    void insertar(std::vector<int> dim) {insertar(root, dim, 0);}
};
#endif // KDTREE_H_
