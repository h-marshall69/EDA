#include <iostream>
#include "Kdtree.h"
using namespace std;
int main() {
    Kdtree *kd = new Kdtree();
    vector<int> a(2);
    a[0] = 40;
    a[1] = 45;
    vector<int> b(2);
    b[0] = 15;
    b[1] = 70;
    vector<int> c(2);
    c[0] = 70;
    c[1] = 10;
    vector<int> d(2);
    d[0] = 69;
    d[1] = 50;
    vector<int> e(2);
    e[0] = 66;
    e[1] = 85;
    vector<int> f(2);
    f[0] = 85;
    f[1] = 90;
    kd->insertar(a);
    kd->insertar(b);
    kd->insertar(c);
    kd->insertar(d);
    kd->insertar(e);
    kd->insertar(f);
    //cout << kd->root->right->right->right->nivel << endl;
    //cout << kd->root->right->right->right->dim[1] << endl;
    vector<int> ab(2);
    ab[0] = 40;
    ab[1] = 45;
    kd->prueba(ab);
    return 0;
}