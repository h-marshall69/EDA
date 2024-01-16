/*******************************************************************************
 Created by Marshall Abadeer on 01/15/24.
*******************************************************************************/

#ifndef BKTREE_H_
#define BKTREE_H_
#include <iostream>
#include <vector>
#include <map>
#include <memory>
class Nodo {
public:
    std::string word;
    std::map<int, std::unique_ptr<Nodo>> next;
    Nodo(std::string x = "") : word(x) {}
    Nodo() : word("") {}
};

class BKtree {
private:
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
    void insertar(std::unique_ptr<Nodo>& root, std::string data) {
        int distance = levenshtein_distance(data, root->word);
        if(root->next.find(distance) == root->next.end()) {
            root->next.insert(std::make_pair(distance, std::make_unique<Nodo>(data)));
        }
        else {
            insertar(root->next[distance], data);
        }
    }
    void similares(std::vector<std::string>& result, const std::unique_ptr<Nodo> & root, std::string data, int tolerancia) {
        if(root) {
            int distance = levenshtein_distance(data, root->word);
            if(distance <= tolerancia) {
                //std::cout << root->word << " : " << data << " " << distance << std::endl;
                result.push_back(root->word);
                for (const auto& r : root->next) {
                    similares(result , r.second, data, tolerancia);
                }
            }
        }
    }
    void xmostrar(const std::map<int, std::unique_ptr<Nodo>>& next, std::string data) {
        for(const auto& n : next) {
            std::cout << "p:" << data << "->" << n.first << ":" << n.second->word << std::endl;
            xmostrar(n.second->next, n.second->word);
        }
    }
    void mostrar(HDC hdc, double x, double y, const std::map<int, std::unique_ptr<Nodo>>& next) {
        for(const auto& n : next) {
            //std::cout << n.first << " " << n.second->word << " " << x << ", " << y << std::endl;
            char arr[n.second->word.length() + 1];
            strcpy(arr, n.second->word.c_str());
            TextOut(hdc, x, y, arr, strlen(arr));
            if(!(n.second->next.empty())) {
                mostrar(hdc, x/root->next.size() + x, y + 100, n.second->next);
            }
            x += x;
        }
    }

public:
    std::unique_ptr<Nodo> root;
    BKtree() : root(nullptr) {}
    void insertar(std::string data) {
        if(root == nullptr){
            root = std::make_unique<Nodo>(data);
            return;
        }
        insertar(root, data);
    }
    std::vector<std::string> similares(std::string data, int tolerancia) {
        std::vector<std::string> result;
        similares(result, root, data, tolerancia);
        return result;
    }
    void xmostrar() {
        if(root) {
            std::cout << root->word << std::endl;
            if(!(root->next.empty())) {
                xmostrar(root->next, root->word);
            }
        }
    }
    void mostrar(HDC hdc, double x, double y) {
        if(root) {
            //std::cout << root->word << " "<< x << ", " << y << std::endl;
            char arr[root->word.length() + 1];
            strcpy(arr, root->word.c_str());
            TextOut(hdc, x, y, arr, strlen(arr));
            if(!(root->next.empty())) {
                mostrar(hdc, x/root->next.size(), y + 100, root->next);
            }
        }
    }
};
#endif // BKTREE_H_
