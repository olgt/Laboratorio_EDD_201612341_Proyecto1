#ifndef NODO_MATRIZ_H
#define NODO_MATRIZ_H


using namespace std;
#include <iostream>

class Nodo_Matriz
{
    Nodo_Matriz *derecha;
    Nodo_Matriz *izquierda;
    Nodo_Matriz *abajo;
    Nodo_Matriz *arriba;

public:
    Nodo_Matriz();
    ~Nodo_Matriz();

    Nodo_Matriz *getIzquierda(){return this->izquierda;}
    Nodo_Matriz* getDerecha(){return this->derecha;}
    Nodo_Matriz* getArriba(){return this->arriba;}
    Nodo_Matriz* getAbajo(){return this->abajo;}


    void setIzquierda(Nodo_Matriz* izquierda){
        this->izquierda = izquierda;
    }
    void setDerecha(Nodo_Matriz* derecha){
        this->derecha = derecha;
    }
    void setAbajo(Nodo_Matriz* abajo){
        this->abajo = abajo;
    }
    void setArriba(Nodo_Matriz* arriba){
        this->arriba = arriba;
    }



};

#endif // NODO_MATRIZ_H
