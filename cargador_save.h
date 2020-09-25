#ifndef CARGADOR_SAVE_H
#define CARGADOR_SAVE_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "Arbol_AVL.h"
#include "arbol_binario.h"
#include "Lista_Niveles.h"
#include "Nodo_Nivel.h"
#include "Matriz.h"
#include "Nodo_Matriz.h"
#include "Nodo_Objeto.h"
#include "nodo_binario.h"

using json=nlohmann::json;
using namespace std;

class Cargador_Save
{
private:
    Arbol_AVL* arbolProyectos;
    Arbol_Binario* arbolObjetos;

    public:


    Cargador_Save(Arbol_AVL*, Arbol_Binario*);

    void guardarProyectos();
    void guardarListaNiveles(string &MyFile, NodoArbol* proyectoActual);
    void guardarMatriz(string &MyFile);
    void guardarArbolBinario();

    void recorrerArbol(NodoArbol *raiz, string &MyFile,int &pos);
    void guardarParedes(Nodo_Nivel* nodoNivel, string &MyFile);
    void guardarVentanas(Nodo_Nivel* nodoNivel, string &MyFile);
    void guardarObjetos(Nodo_Nivel* nodoNivel, string &MyFile);

};

#endif // CARGADOR_SAVE_H
