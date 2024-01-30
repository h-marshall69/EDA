#ifndef VPTREE_H_
#define VPTREE_H_
#include <iostream>
#include <memory>
#include <math.h>
#include <vector>
using namespace std;

class P {
public:
    double x, y;
    P(double x = 0., double y = 0.) : x(x), y(y) {}
    bool operator!=(const P& other) const {
        return x != other.x || y != other.y;
    }
    bool operator==(const P& other) const {
        return x == other.x && y == other.y;
    }
};

double distancia(const P& a, const P& b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

int partition(vector<pair<double, P>>& arr, int low, int high) {
    double pivot = arr[high].first;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].first < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<pair<double, P>>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

class Node {
public:
    std::vector<P> data;
    P vp;
    double r;
    int i;
    std::unique_ptr<Node> inside;
    std::unique_ptr<Node> ouside;
    Node () {inside = nullptr; ouside = nullptr;}
};

class Vptree {
private:
    void insert(unique_ptr<Node>& root, P data) {
        if(root) {
            root->data.push_back(data);
            std::vector<std::pair<double, P>> cv;
            for(int i = 0; i < root->data.size(); i++) {
                int j = 0;
                while(j < i) {
                    cv.push_back(std::make_pair(distancia(root->data[i], root->data[j]), root->data[j]));
                    j++;
                }
            }
            quickSort(cv, 0, cv.size() - 1);
            root->vp = cv[cv.size()/2].second;
            root->r = cv[cv.size()/2].first;

            root->inside = nullptr;
            root->ouside = nullptr;
            for(auto d : root->data) {
                if(d != root->vp) {
                    if(distancia(d, root->vp) <= root->r)
                        insert(root->inside, d);
                    else
                        insert(root->ouside, d);
                }
            }
            //cout << root->vp << " ";
        }
        else {
            root = make_unique<Node>();
            root->data.push_back(data);
            root->vp = root->data[0];
            root->r = 0;
            //cout << root->vp << " ";
        }
        //cout << ", ";
    }

    void preorden(unique_ptr<Node>& root, char c) {
        if(root) {
            cout << c << "(" << root->vp.x << ", " << root->vp.y << ") -> " << root->r << " ";
            preorden(root->inside, 'i');
            preorden(root->ouside, 'o');
        }
    }
    void xpreorden(HDC hdc, std::unique_ptr<Node>& root, int x,int y,int xa,int ya,int a) {
        if(root) {
            char Cad[20];
            itoa(root->vp.x, Cad, 10);
            int len = strlen(Cad);
            TextOut(hdc, x - 30, y, Cad, len);

            char Cad1[20];
            itoa(root->vp.y, Cad1, 10);
            int len1 = strlen(Cad1);
            TextOut(hdc, x + 5, y, Cad1, len1);

            Arc(hdc, root->vp.x - root->r, root->vp.y - root->r, root->vp.x + root->r, root->vp.y + root->r, 0, 0, 0, 0);

            xpreorden(hdc, root->inside, x - a/2, y + 40, x, y, a/2);

            xpreorden(hdc, root->ouside, x+a/2, y+40, x, y, a/2);

            MoveToEx(hdc, xa, ya, NULL);
            LineTo(hdc, x, y);
        }
    }
    /*void eliminar(std::unique_ptr<Node>& root, std::vector<P>& d_t, P p) {
        if(root) {
            int dis = distancia(root->vp, p);
            if (d <= root->vp)
                insertar(root->inside, p);
            else
                insertar(root->der, p, radio);
        }
    }*/
    void eliminar(std::vector<P>& d_t, P p) {
        if(!d_t.empty()) {
            for (auto it = d_t.begin(); it != d_t.end(); ++it) {

                if (*it == p) {
                    d_t.erase(it);
                    break;
                }
            }
        }
    }

public:
    std::unique_ptr<Node> root;
    std::vector<P> data_set;
    Vptree() {root = nullptr;}
    void insert(P data) {
        data_set.push_back(data);
        //cout << data_set[data_set.size()/2].x << " ";
    }
    void buil_tree() {
        root = nullptr;
        for(auto d : data_set)
            insert(root, d);
        //cout << "; ";

    }
    void preorden() {preorden(root, 'r');}
    void xpreorden(HDC hdc, int x, int y, int xa, int ya, int a) {
        xpreorden(hdc, root, x, y, xa, ya, a);
    }
    void eliminar(P p) {eliminar(data_set, p);}
};

#endif // VPTREE_H_
