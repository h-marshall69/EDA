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
    void xpreorden(HDC hdc, std::unique_ptr<Node>& root) {
        if(root) {
            Arc(hdc, root->vp.x - root->r, root->vp.y - root->r, root->vp.x + root->r, root->vp.y + root->r, 0, 0, 0, 0);
            //Ellipse(hdc, root->vp.x - root->r, root->vp.y - root->r, root->vp.x + root->r, root->vp.y + root->r);
            xpreorden(hdc, root->inside);
            //Ellipse(hdc, root->vp.x - root->r, root->vp.y - root->r, root->vp.x + root->r, root->vp.y + root->r);
            xpreorden(hdc, root->ouside);
            //Ellipse(hdc, root->vp.x - root->r, root->vp.y - root->r, root->vp.x + root->r, root->vp.y + root->r);
            //Arc(hdc, root->vp.x - root->r, root->vp.y - root->r, root->vp.x + root->r, root->vp.y + root->r, 0, 0, 0, 0);
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
    void xpreorden(HDC hdc) {xpreorden(hdc, root);}
};

/*int main() {
    Vptree tree;
    tree.insert(P(603, 846));
    tree.insert(P(654, 812));
    tree.insert(P(543, 436));
    tree.insert(P(756, 886));
    tree.insert(P(434, 845));
    cout<<endl;

    tree.buil_tree();
    tree.preorden();

    return 0;
}*/

#endif // VPTREE_H_
