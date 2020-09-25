#ifndef NODO_OBJETO_H
#define NODO_OBJETO_H

#include <string>
#include "Nodo_Matriz.h"
using namespace std;


class Nodo_Objeto:public Nodo_Matriz
{
private:
    int id;
    string objeto;
    char letra;
    string color;
    int x;
    int y;

public:
    Nodo_Objeto(int id, string objeto, char letra, string color, int x, int y);

    string getObjeto();
    int getId();
    void setObjeto(string objeto);
    void setX(int);
    int getX();
    void setY(int);
    int getY();
    string getColor();
    void setLetra(char letra);
    void setColor(string color);
    void setId(int id);
    char getLetra();
    string getXY();
};

#endif // NODO_OBJETO_H
