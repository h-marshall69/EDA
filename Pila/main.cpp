#include <iostream>
#include "Lista.h"
using namespace std;
int main() {
    Lista<int> *hg = new Lista<int>(23);
    hg->print();
    return 0;
}