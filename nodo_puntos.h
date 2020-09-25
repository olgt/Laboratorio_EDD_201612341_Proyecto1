#ifndef NODO_PUNTOS_H
#define NODO_PUNTOS_H

#include <iostream>
using namespace std;

class Nodo_Puntos
{
private:
    int x;
    int y;
    Nodo_Puntos *siguiente;

public:
    Nodo_Puntos(int x, int y);

    void setSiguiente(Nodo_Puntos *n);
    void setAnterior(Nodo_Puntos  *n);
    Nodo_Puntos* getSiguiente();

    int getSizeX();
    int getSizeY();

    int getX();
    int getY();
};
#endif // NODO_PUNTOS_H
