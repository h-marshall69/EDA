#ifndef LISTADESORDENADA_H_
#define LISTADESORDENADA_H_
#include "Lista.h"
template <class T>
class ListaDesordena : public Lista<T> {
public:
    bool search(const T&) const;
    void insertar_inicio(const T&) const;
    void insertar_final(const T&) const;
    void borrar_nodo(const T&) const;
};

template <class T>
bool ListaDesordena<T>::search(const T& item) const {
    Node<T> *current;
    bool found = false;
    current = first;
    while(current != nullptr && !found)
        (current->dato == item) ? found = true : current = current->link;
    return found;
}

template <class T>
void ListaDesordena<T>::insertar_inicio(const T& item) const {
    Nodo<T> *new_nodo;
    new_nodo = new Nodo<T>(item);
    first = new_nodo;
    count++;

    if(last == nullptr)
        last = new_nodo;
}

template <class T>
void ListaDesordena<T>::insertar_final(const T& item) const {
    Nodo<T> *new_nodo;
    new_nodo = new Node<T>(item);

    if(first == nullptr) {
        first = new_nodo;
        last = new_nodo;
        count++;
    }else {
        last->link = new_nodo;
        last = new_nodo;
        count++;
    }
}

template <class T>
void ListaDesordena<T>::borrar_nodo(const T& item) const {
    Nodo<T> *current;
    Nodo<T> *trail_current;
    bool found;

    if(first == nullptr)
        std::cout << "No se puede elinar de una lista vacia.\n";
    else {
        if(first->dato == item) {
            current = first;
            first = first->link;
            count--;
            if(first == nullptr)
                last = nullptr;
            delete current;
        }
        else {
            found = false;
            trail_current = first;
            current = first->link;

            while(current != nullptr && !found) {
                if(current->dato != item) {
                    trail_current = current;
                    current = current->link;
                }
                else {
                    found = true;
                }
            }
            if(found) {
                trail_current->link = current->link;
                count--;
                if(last == current)
                    last = trail_current;
                delete current;
            }
            else
                std::cout << "El item a eliminar no estara en la lista.\n";
        }
    }
}

#endif