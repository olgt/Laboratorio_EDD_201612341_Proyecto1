#ifndef LISTA_PUNTOS_H
#define LISTA_PUNTOS_H

#include "nodo_puntos.h"
#include <iostream>
using namespace std;

class Lista_Puntos
{
public:
    Lista_Puntos();
    ~Lista_Puntos();

    void Delete(Nodo_Puntos*);

    void deleteNode(int x, int y);
    void addNode(Nodo_Puntos *nuevo);
    void searchNode(int id);
    void printLinkedList();

    Nodo_Puntos *gethead();

    int getSizeX();
    int getSizeY();
    int getSizeNodos();
    Nodo_Puntos *getPunto(int pos);
    Lista_Puntos* copiarEstaLista();
private:
    Nodo_Puntos *head;
    Nodo_Puntos *tail;

};

#endif // LISTA_PUNTOS_H
