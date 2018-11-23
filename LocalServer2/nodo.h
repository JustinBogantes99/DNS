#ifndef NODO_H
#define NODO_H


template <class T>
class Nodo
{
private:
    T dato;
    Nodo* siguiente,* anterior;
public:
    typedef T type;

    Nodo(T valor)
    {
    dato = valor;
    siguiente = 0; // 0 es el puntero NULL en C++
    }

    Nodo(T p, Nodo* n) // crea el nodo y lo enlaza a n
    {
    dato = p;
    siguiente = n;
    }

    T getDato()
    {
        return dato;
    }

    void setDato(T x){
        dato = x;
    }

    Nodo* getSiguiente() const
    {
        return siguiente;
    }
    void setSiguiente(Nodo* sgte)
    {
        siguiente = sgte;
    }

    Nodo* getAnterior() const
    {
        return anterior;
    }

    void setAnterior(Nodo* ant){
        anterior = ant;
    }

};


#endif /* NODO_H */
