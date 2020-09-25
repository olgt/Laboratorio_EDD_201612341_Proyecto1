#include "nodo_puntos.h"

Nodo_Puntos::Nodo_Puntos(int x, int y)
{
    this->x = x;
    this->y = y;
    this->siguiente = NULL;
}


void Nodo_Puntos::setSiguiente(Nodo_Puntos *n){
    this->siguiente = n;
}

int Nodo_Puntos::getX(){
    return this->x;
}

int Nodo_Puntos::getY(){
    return this->y;
}

Nodo_Puntos* Nodo_Puntos::getSiguiente(){
    return this->siguiente;
}

