#ifndef NODO_CONSTRUCCION_H
#define NODO_CONSTRUCCION_H

#include <Nodo_Nivel.h>
#include <iostream>
#include <stdlib.h>
#include <utilities.h>
using namespace std;


class Lista_Niveles
{

private:
    Nodo_Nivel *head;
    Nodo_Nivel *tail;
    int size;

public:
    Lista_Niveles();
    ~Lista_Niveles();

    void Delete(Nodo_Nivel*);

    void addNode(Nodo_Nivel *nuevo);
    void searchNode(int id);
    void deleteNode(int id);
    int getSize();
    int getId();
    void imprimirNiveles();
    void graficarNiveles(string nombreProyecto);

    Nodo_Nivel* getHead();
    Nodo_Nivel* getTail();
    Nodo_Nivel* getNodo(int id);
    Nodo_Nivel* nivelConMasEspacio();
    Nodo_Nivel* nivelConMasParedes();
    Nodo_Nivel* nivelConMenosParedes();
    Nodo_Nivel* nivelConMasEspacioMenosVentanas();
    Nodo_Nivel* nivelConMasEspacioMasVentanas();
    void nivelesPorNumeroDeObjetos();
    int ** llenarArray(int ** proyectoArray, Nodo_Nivel* nodo_Actual, int &pos);
    int ** llenarArrayProyectosNiveles();
    void aumentarObjetos(int cantidad);
    void graficarTodosABB(string nameProyecto);

};

#endif // NODO_CONSTRUCCION_H
