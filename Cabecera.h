#ifndef CABECERA_H
#define CABECERA_H

#include <string>
#include "Nodo_Matriz.h"
using namespace std;

class Cabecera:public Nodo_Matriz
{
private:
    int nombre;

public:
    Cabecera(int pos);

    void setPos(int);
    int getPos();
};

#endif // CABECERA_H
