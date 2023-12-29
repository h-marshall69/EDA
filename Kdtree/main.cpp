#include <iostream>
#include "Kdtree.h"
using namespace std;

int main() {
    unique_ptr<Kdtree> kd = make_unique<Kdtree>();

    vector<std::vector<int>> valores = {
        {40, 45},
        {15, 70},
        {70, 10},
        {69, 50},
        {66, 85},
        {85, 90}
    };

    // Insertar valores en el árbol
    for (const auto& val : valores) {
        kd->insertar(val);
    }
    
    // Buscar un nodo
    vector<int> nodo_a_buscar = {85, 90};
    Knode* nodo_encontrado = kd->buscar(nodo_a_buscar);
    if (nodo_encontrado) {
        cout << "Nodo encontrado en el nivel: " << nodo_encontrado->nivel << endl;
    } else {
        cout << "Nodo no encontrado." << endl;
    }
    
    // Eliminar un nodo
    vector<int> nodo_a_eliminar = {70, 10};
    bool eliminado = kd->eliminar(nodo_a_eliminar);
    if (eliminado) {
        cout << "Nodo eliminado correctamente." << endl;
    } else {
        cout << "Nodo no encontrado para eliminar." << endl;
    }
    return 0;
}
