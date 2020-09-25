#ifndef NODOARBOL_H
#define NODOARBOL_H

#include <Lista_Niveles.h>
#include <bits/stdc++.h>


class NodoArbol
{
private:
    NodoArbol *hijoDerecho;
    NodoArbol *hijoIzquierdo;

    string nombre;
    int codigo;
    int id;
    Lista_Niveles *niveles;

    int factorE;


public:
    NodoArbol(string nombre, Lista_Niveles* niveles, int id); //Debo Poner *Lista de Niveles como parametro

    void setCodigo(string nombre);
    int sumarCaracteres();
    int getCodigo();
    int getId();

    string getName();

    void setid(int id);

    void setIzquierda(NodoArbol* izq);
    void setDerecha(NodoArbol* der);

    NodoArbol* getDerecha();
    NodoArbol* getIzquierda();

    void setFactor(int factor);
    int getFactor();

    NodoArbol* getPadre();
    void setPadre(NodoArbol* padre);

    Lista_Niveles* getListaNiveles();

};


#endif // NODOARBOL_H
