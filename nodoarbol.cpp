#include "nodoarbol.h"

NodoArbol::NodoArbol(string nombre, Lista_Niveles* niveles, int id) //Poner lista de niveles
{
    this->nombre = nombre;
    this->niveles = niveles;
    this->codigo = sumarCaracteres();
    this->hijoDerecho=NULL;
    this->hijoIzquierdo=NULL;
    this->factorE=0;
    this->id = id;
}


int NodoArbol::sumarCaracteres(){

    int codigo = 0;
    string nombre = this->nombre;
    int n = nombre.length();

    char char_array[n+1];
    strcpy(char_array, nombre.c_str()); //Metodo agrega los caracteres al array

    for(int i = 0; i < n; i++){
        codigo += (int)char_array[i];
    }
    cout<<codigo<<endl;
    return codigo;
}

int NodoArbol::getCodigo(){
    return this->codigo;
}

string NodoArbol::getName(){
    return this->nombre;
}


void NodoArbol::setIzquierda(NodoArbol* izq){
    this->hijoIzquierdo = izq;
}

void NodoArbol::setDerecha(NodoArbol* der){
    this->hijoDerecho = der;
}

NodoArbol* NodoArbol::getDerecha(){
    return this->hijoDerecho;
}

NodoArbol* NodoArbol::getIzquierda(){
    return this->hijoIzquierdo;
}


int NodoArbol::getId(){
    return this->id;
}

void NodoArbol::setid(int id){
    this->id = id;
}

//Para arbol AVL
void NodoArbol::setFactor(int factor){
    this->factorE = factor;
}

int NodoArbol::getFactor(){
    return this->factorE;
}

Lista_Niveles* NodoArbol::getListaNiveles(){
    return this->niveles;
}

