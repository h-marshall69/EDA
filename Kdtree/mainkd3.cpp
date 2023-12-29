#include <iostream>
#include "Kdtree.h"
using namespace std;

int main() {
   unique_ptr<Kdtree> kd = make_unique<Kdtree>();

    std::vector<std::vector<int>> valores = {
        {10, 20, 30},
        {25, 30, 15},
        {5, 15, 25},
        {30, 10, 20},
        {15, 5, 35},
        {20, 35, 5}
    };
    

    // Insertar valores en el árbol
    for (const auto& val : valores) {
        kd->insertar(val);
    }
    kd->preorden();
    cout << endl;
    // Buscar un nodo
    vector<int> nodo_a_buscar = {30, 10, 20};
    Knode* nodo_encontrado = kd->buscar(nodo_a_buscar);
    if (nodo_encontrado) {
        cout << "Nodo encontrado en el nivel: " << nodo_encontrado->nivel << endl;
    } else {
        cout << "Nodo no encontrado." << endl;
    }
    
    // Eliminar un nodo
    vector<int> nodo_a_eliminar = {10, 20, 30};
    bool eliminado = kd->eliminar(nodo_a_eliminar);
    if (eliminado) {
        cout << "Nodo eliminado correctamente." << endl;
    } else {
        cout << "Nodo no encontrado para eliminar." << endl;
    }
    cout << endl; 
    kd->preorden();
    return 0;
}