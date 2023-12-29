#ifndef KDTREE_H_
#define KDTREE_H_

#include <vector>
#include <memory>

bool operator==(const std::vector<int>& left, const std::vector<int>& right) {
    if (left.size() != right.size())
        return false;

    for (size_t i = 0; i < left.size(); ++i) {
        if (left[i] != right[i])
            return false;
    }
    return true;
}

class Knode {
public:
    std::vector<int> dim;
    int nivel;
    std::unique_ptr<Knode> left;
    std::unique_ptr<Knode> right;

    Knode() : nivel(0), left(nullptr), right(nullptr) {}
    explicit Knode(const std::vector<int>& d) : dim(d), nivel(0), left(nullptr), right(nullptr) {}
};

class Kdtree {
private:
    void insertar(std::unique_ptr<Knode>& current, const std::vector<int>& dim, int n) {
        if (!current) {
            current = std::make_unique<Knode>(dim);
            current->nivel = n;
        } else {
            if (dim[n] < current->dim[n]) {
                if (n + 1 == static_cast<int>(dim.size()))
                    n = -1;
                insertar(current->left, dim, n + 1);
            } else {
                if (n + 1 == static_cast<int>(dim.size()))
                    n = -1;
                insertar(current->right, dim, n + 1);
            }
        }
    }

    Knode* buscar(const std::unique_ptr<Knode>& current, const std::vector<int>& dim);
    
    bool eliminar(std::unique_ptr<Knode>& current, const std::vector<int>& dim, int n) {
        if (!current) {
            return false; // El nodo no existe en el árbol
        } else {
            if (current->dim == dim) {
                // Encontrado el nodo a eliminar
                if (current->right == nullptr && current->left == nullptr) {
                    current = nullptr; // Actualizar el puntero
                    return true;
                } else {
                    // Encontrar el sucesor inmediato
                    Knode *temp = current->right.get();
                    while (temp->left != nullptr) {
                        temp = temp->left.get();
                    }
                    // Copiar los valores del sucesor inmediato al nodo actual
                    current->dim = temp->dim;
                    // Eliminar el sucesor inmediato
                    eliminar(current->right, temp->dim, n + 1);
                    return true;
                }
            } else {
                if (dim[n] < current->dim[n]) {
                    return eliminar(current->left, dim, (n + 1) % dim.size());
                } else {
                    return eliminar(current->right, dim, (n + 1) % dim.size());
                }
            }
        }
    }

public:
    std::unique_ptr<Knode> root;

    Kdtree() : root(nullptr) {}

    void insertar(const std::vector<int>& dim) {
        insertar(root, dim, 0);
    }

    Knode* buscar(const std::vector<int>& dim) {
        return buscar(root, dim);
    }

    void prueba(const std::vector<int>& dim) {
        Knode* tm = buscar(dim);
        if (tm)
            std::cout << tm->nivel;
    }
    
    bool eliminar(const std::vector<int>& dim) {
        return eliminar(root, dim, 0);
    }
};

Knode* Kdtree::buscar(const std::unique_ptr<Knode>& current, const std::vector<int>& dim) {
    if (current) {
        int n = current->nivel % dim.size();
        if (current->dim == dim) {
            return current.get();
        } else {
            if (current->dim[n] > dim[n])
                return buscar(current->left, dim);
            else
                return buscar(current->right, dim);
        }
    }
    return nullptr;
}

#endif // KDTREE_H_