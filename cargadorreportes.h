#ifndef CARGADORREPORTES_H
#define CARGADORREPORTES_H

#include "Arbol_AVL.h"
#include "arbol_binario.h"
#include "Lista_Niveles.h"
#include "Nodo_Nivel.h"
#include "Matriz.h"
#include "Nodo_Matriz.h"
#include "Nodo_Objeto.h"
#include "nodo_binario.h"

class cargadorReportes
{

    Arbol_AVL* proyectos;
    Arbol_Binario* arbolObjetos;

public:
    cargadorReportes(Arbol_AVL* proyectos, Arbol_Binario* arbolObjetos);

    void mostrarOpciones();
    void imprimirOpciones();

    void reporteProyectoMayorNumeroNivelesAscendente();
    void reporteProyectoMayorNumeroNivelesDescendente();
    void reporteProyectoNivelesPorObjeto();
    void reporteNivelMasEspacio();
    void reporteNivelMenosParedes();
    void reporteNivelMasParedes();
    void reporteNivelMasEspacioMasVentanas();
    void reporteNivelMasEspacioMenosVentanas();
    int * llenarArray(int proyectoArray[][2], Nodo_Nivel* nodo_Actual, int &pos);

};

#endif // CARGADORREPORTES_H
