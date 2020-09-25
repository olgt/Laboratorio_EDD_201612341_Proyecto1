#ifndef NODO_BINARIO_H
#define NODO_BINARIO_H

#include <iostream>
#include "string.h"
#include "lista_puntos.h"
using namespace std;

class Nodo_Binario
{
private:

    Nodo_Binario *hijoDerecho;
    Nodo_Binario *hijoIzquierdo;
    Nodo_Binario *padre;
    Lista_Puntos *xy;

    int id;
    string nombre;
    char letra;
    string color;
    int x;
    int y;


public:
    Nodo_Binario(int id, string nombre, char letra, string color, Lista_Puntos* xy, Nodo_Binario* padre);

    void setIzquierda(Nodo_Binario* izq);
    void setDerecha(Nodo_Binario* der);

    Nodo_Binario* getDerecha();
    Nodo_Binario* getIzquierda();

    int getId();
    string getName();
    char getLetra();
    string getColor();
    int getX();
    int getY();
    Lista_Puntos *getListaPuntos();

    void setId(int id);
    void setName(string nombre);
    void setLetra(char letra);
    void setColor(string color);
    void setListaPuntos(Lista_Puntos* xy);
    void setPadre(Nodo_Binario* padre);

    //Metodos para elimnar Nodo
    void eliminarNodo(int idObjeto);
    Nodo_Binario* getPadre();

};

#endif // NODO_BINARIO_H
