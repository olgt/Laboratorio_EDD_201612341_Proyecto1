#ifndef NODONIVEL_H
#define NODONIVEL_H

#include <iostream>
#include <utilities.h>
#include "Matriz.h"
#include "arbol_binario.h"

using namespace std;

class Nodo_Nivel
{
private:
    int id;
    Matriz* matriz;
    Arbol_Binario* abb;
    Arbol_Binario* auxAbb;
    Nodo_Nivel *siguiente;
    Nodo_Nivel *anterior;

public:
    Nodo_Nivel(int id, Matriz* matriz, Arbol_Binario* abb);

    ~Nodo_Nivel();

    void imprimirOpciones();

    void setSiguiente(Nodo_Nivel *n);
    void setAnterior(Nodo_Nivel *n);
    Nodo_Nivel * getSiguiente();
    Nodo_Nivel * getAnterior();
    int getId();

    Matriz* getMatriz();
    void setMatriz(Matriz* nuevaMatriz);
    void setId(int id);

    void setABB(Arbol_Binario* abb);
    Arbol_Binario* getABB();

};

#endif // NODONIVEL_H
