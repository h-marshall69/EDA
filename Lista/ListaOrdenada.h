#ifndef LISTAORDENADA_H_
#define LISTAORDENADA_H_
#include "Lista.h"
template <class T>
class ListaOrdena : public Lista<T>{
public:
    bool search(const T&) const;
    void insertar_inicio(const T&) const;
    void insertar_final(const T&) const;
    void borrar_nodo(const T&) const;
};

template <class T>
bool ListaOrdena<T>::search(const T& item) const{
    Node<T> *current;
    bool found = false;
    current = first;
    while(current != nullptr && !found)
        (current->dato == item) ? found = true : current = current->link;
}

#endif