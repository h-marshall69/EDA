#ifndef LISTA_H_
#define LISTA_H_
#include "Nodo.h"
template <class T>
class ListaIterator {
public:
    ListaIterator();
    ListaIterator(Nodo<T>*);
    T operator*();
    ListaIterator<T> operator++();
    bool operator==(const ListaIterator<T>&) const;
    bool operator!=(const ListaIterator<T>&) const;
private:
    Nodo<T> *current;
};

template <class T>
ListaIterator<T>::ListaIterator() {
    current = nullptr;
}

template <class T>
ListaIterator<T>::ListaIterator(Nodo<T> *ptr) {
    current = ptr;
}

template <class T>
T ListaIterator<T>::operator*() {
    return current->dato;
}

template <class T>
ListaIterator<T> ListaIterator<T>::operator++() {
    current = current->link;
    return *this;
}

template <class T>
bool ListaIterator<T>::operator==(const ListaIterator<T>& right) const {
    return current == right.current;
}

template <class T>
bool ListaIterator<T>::operator!=(const ListaIterator<T>& right) const {
    return current != right.current;
}

template <class T>
class Lista {
public:
    const Lista<T>& operator=(const Lista<T>&);
    bool empty() const;
    void print() const;
    int length() const;
    void destroy();
    T front() const;
    T back() const;
    virtual bool search(const T&) const = 0;
    virtual void insertar_inicio(const T&) = 0;
    virtual void insertar_final(const T&) = 0;
    virtual void borrar_nodo(const T&) = 0;
    ListaIterator<T> begin();
    ListaIterator<T> end();
    Lista();
    Lista(T);
    Lista(const Lista<T>&);
    ~Lista();
protected:
    int count;
    Nodo<T> *first;
    Nodo<T> *last;
private:
    void copiar(const Lista<T>&);
};

template <class T>
bool Lista<T>::empty() const{
    return first == nullptr;
}

template <class T>
Lista<T>::Lista() {
    first = nullptr;
    last = nullptr;
    count = 0;
}

template <class T>
Lista<T>::Lista(T dato) {
    first = new Nodo<T>();
    first->dato = dato;
    last = first;
    count = 1;
}

template <class T>
void Lista<T>::destroy(){
    Nodo<T> *temp;
    while(first != nullptr){
        temp = first;
        first = first->link;
        delete temp;
    }
    last = nullptr;
    count = 0;
}

template <class T>
void Lista<T>::print() const{
    Nodo<T> *current = first;
    while(current != nullptr){
        std::cout << current->dato << " ";
        current = current->link;
    }
}

template <class T>
int Lista<T>::length() const{
    return count;
}

template <class T>
T Lista<T>::front() const{
    assert(first != nullptr);
    return first->dato;
}

template <class T>
T Lista<T>::back() const{
    assert(last != nullptr);
    return last->dato;
}

template <class T>
ListaIterator<T> Lista<T>::begin(){
    ListaIterator<T> temp(first);
    return temp;
}

template <class T>
ListaIterator<T> Lista<T>::end(){
    ListaIterator<T> temp(last);
    return temp;
}

template <class T>
void Lista<T>::copiar(const Lista<T>& otra_lista){
    Nodo<T> *new_nodo = nullptr;
    Nodo<T> *current = nullptr;
    if(first != nullptr){
        destroy();
    }
    if(otra_lista.first == nullptr){
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else{
        current = otra_lista.first;
        count = otra_lista.count;
        first = new Nodo<T>(current->dato);
        last = first;
        current = current->link;
        while(current != nullptr){
            new_nodo = new Nodo<T>(current->dato);
            last->link = new_nodo;
            last = new_nodo;
            current = current->link;
        }
    }
}

template <class T>
Lista<T>::~Lista(){
    destroy();
}

template <class T>
Lista<T>::Lista(const Lista<T>& otra_lista){
    first = nullptr;
    copiar(otra_lista);
}

template <class T>
const Lista<T>& Lista<T>::operator=(const Lista<T>& otra_lista){
    if(this != &otra_lista){
        copiar(otra_lista);
    }
    return *this;
}
#endif