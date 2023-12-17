#ifndef LISTAORDENADA_H_
#define LISTAORDENADA_H_
#include "Lista.h"
template <class T>
class ListaOrdena : public Lista<T> {
public:
    bool search(const T&) const;
    void insertar(const T&) const;
    void insertar_inicio(const T&) const;
    void insertar_final(const T&) const;
    void borrar_nodo(const T&) const;
};

template <class T>
bool ListaOrdena<T>::search(const T& item) const {
    bool found = false;
    Nodo<T> *current;
    current = first;

    while(current != nullptr && !found)
        (current->dato == item) ? found = true : current = current->link;
    
    return found;
}

template <class T>
void ListaOrdena<T>::insertar(const T& item) const {
    Nodo<T> *current;
    Nodo<T> *trail_current;
    Nodo<T> *new_nodo;

    bool found;

    new_nodo = new Nodo<T>(item);

    if(first == nullptr) {
        first = new_nodo;
        last = new_nodo;
        count++;
    }
    else {
        current = first;
        found = false;

        while(current != nullptr && !found) {
            if(current->dato >= item)
                found = true;
            else {
                trail_current = current;
                current = current->link;
            }
        }

        if(current == first) {
            new_nodo->link = first;
            first = new_nodo;
            count++;
        }
        else {
            trail_current->link = new_nodo;
            new_nodo->link = current;

            if(current == nullptr)
                last = new_nodo;

            count++;
        }
    }
}

template <class T>
void ListaOrdena<T>::insertar_inicio(const T& item) const {
    insertar(item);
}

template <class T>
void ListaOrdena<T>::insertar_final(const T& item) const {
    insertar(item);
}

template <class T>
void ListaOrdena<T>::borrar_nodo(const T& item) const {
    Nodo<T> *current;
    Nodo<T> *trail_current;
    bool found;

    if(first == nullptr)
        std::cout << "No se puede eliminar de una lista vacia.\n";
    else {
        current = first;
        found = false;

        while(current != nullptr && !found) {
            if(current->dato >= item)
                found = true;
            else {
                trail_current = current;
                current = current->link;
            }
        }

        if(current == nullptr)
            std::cout << "El item a eliminar no esta en la lista.\n";
        else {
            if(current->dato == item) {
                if(first == current) {
                    first = first->link;

                    if(first == nullptr)
                        last = nullptr;

                    delete current;
                }
                else {
                    trail_current->link = current->link;

                    if(current == last)
                        last = trail_current;

                    delete current;
                }
                count--;
            }
            else
                std::cout << "El item a eliminar no esta en la lista.\n";
        }
    }
}

#endif