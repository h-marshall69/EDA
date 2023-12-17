#ifndef NODO_H_
#define NODO_H_
template <class T>
class Nodo {
public:
    Nodo<T> *link;
    T dato;

    Nodo();
    Nodo(T);
};

template <class T>
Nodo<T>::Nodo() {
    link = nullptr;
}

template <class T>
Nodo<T>::Nodo(T dato) {
    this->dato = dato;
    link = nullptr;
}
#endif