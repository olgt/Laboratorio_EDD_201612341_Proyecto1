#include "Nodo_Matriz.h"

Nodo_Matriz::Nodo_Matriz()
{
    this->izquierda = NULL;
    this->derecha = NULL;
    this->arriba = NULL;
    this->abajo = NULL;
}

Nodo_Matriz::~Nodo_Matriz(){
    this->abajo = NULL;
    this->arriba = NULL;
    this->derecha = NULL;
    this->izquierda = NULL;
}
