#ifndef BKTREE_H_
#define BKTREE_H_
#include <iostream>
#include <string>
#include <vector>

class Nodo {
public:
    std::string palabra;
    int distancia;
    Nodo *left;
    Nodo *right;

    Nodo(std::string palabra = "", int distancia = -1) : palabra(palabra), distancia(distancia), left(nullptr), right(nullptr) {}
    ~Nodo() {}
};
class BKTree {
private:
    Nodo *root;
    int p_size;
    bool rango(int distancia, int min_dis, int max_dis) {
        return (min_dis <= distancia && distancia <= max_dis);
    }
    int min(int a, int b, int c) {
        int min = a;
        if(b < min)
            min = b;
        if(c < min)
            min = c;
        return min;
    }
    int levenshtein_distance(const std::string a, const std::string b) {
        if (a.length() == 0)
            return b.length();
        if (b.length() == 0)
            return a.length();

        int m = a.size();
        int n = b.size();
        int cost;

        int d[m + 1][n + 1];

        for (int i = 0; i <= m; i++)
            d[i][0] = i;
        for (int i = 0; i <= n; i++)
            d[0][i] = i;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
                d[i][j] = min(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost);
            }
        }
        return d[m][n];
    }
    void insertar(Nodo*& node, std::string data) {
        if (!node) {
            node = new Nodo(data, -1);
        } else {
            int distancia = levenshtein_distance(node->palabra, data);
            if(!distancia)
                return;
            if (distancia <= node->distancia / 2) {
                insertar(node->left, data);
            } else {
                insertar(node->right, data);
            }
        }
    }
    void buscar(Nodo* node, std::vector<std::string>& vec, std::string data, int t, bool& palabra_encontrada) {
        int cur_dis = levenshtein_distance(node->palabra, data);
        int min_dis = cur_dis - t;
        int max_dis = cur_dis + t;

        if(!cur_dis) {
            palabra_encontrada = true;
            return;
        }
        if (cur_dis <= t)
        vec.push_back(node->palabra);

        Nodo* child = node->left;
        if (!child) return;

        while (child) {
            if(rango(child->distancia, min_dis, max_dis))
                buscar(child, vec, data, t, palabra_encontrada);
            child = child->right;
        }
    }
    void inorden(Nodo* node, HDC hdc, int i, int j, int nivel) {
    if (node) {
        // Ajusta la posición según el nivel
        int desplazamientoX = 50 * nivel;
        int desplazamientoY = 50 * nivel;

        inorden(node->left, hdc, i - desplazamientoX, j + desplazamientoY, nivel + 1);

        char arr[node->palabra.length() + 1];
        strcpy(arr, node->palabra.c_str());

        // Dibuja el nodo en la posición actual
        TextOut(hdc, i, j, arr, strlen(arr));

        inorden(node->right, hdc, i + desplazamientoX, j + desplazamientoY, nivel + 1);
    }
}
public:

    BKTree() : root(nullptr), p_size(0) {}

    void insertar(std::string data) {
        insertar(root, data);
    }
    void buscar(std::string data, int t) {
        std::vector<std::string> sujerencias;
        bool palabra_encontrada = false;

        buscar(root, sujerencias, data, t, palabra_encontrada);
        print_sujerencias(sujerencias, palabra_encontrada);
    }
    void print_sujerencias(std::vector<std::string> vec, bool palabra_encontrada) {
        if(palabra_encontrada)
            std::cout << "Word is spelled correctly." << std::endl;
        else if(vec.empty())
            std::cout << "No suggestions found." << std::endl;
        else {
            for(const auto v: vec)
                std::cout << v << std::endl;
        }
    }
    void inorden(HDC hdc, int i = 300, int j = 300) {
        inorden(root, hdc, i, j, 1);
    }
};

#endif
