#ifndef MENUEDITARNIVEL2_H
#define MENUEDITARNIVEL2_H

#include <Arbol_AVL.h>
#include <arbol_binario.h>
#include <nodo_binario.h>
#include <nodoarbol.h>
#include <Nodo_Matriz.h>
#include <Nodo_Nivel.h>
#include <Nodo_Objeto.h>
#include <Lista_Niveles.h>
#include <cargador_proyectos.h>
#include <stdbool.h>


class menuEditarNivel2
{
private:
    NodoArbol* proyecto;
    Arbol_Binario* arbolObjetos;
    int idProyecto;

public:
    menuEditarNivel2(NodoArbol* proyecto, Arbol_Binario* arbolObjetos, int idProyecto);

    void mostrarNiveles();
    void mostrarOpciones();
    void graficarNivel(int id);

    void agregarObjeto(Nodo_Nivel* nivelActual);
    void eliminarObjeto(Nodo_Nivel* nivelActual);
    void eliminarPared(Nodo_Nivel* nivelActual);
    void copiarNivel();
    void crearCantidadPisos();
    void moveObjeto();
    Nodo_Objeto* metodoGiro(Nodo_Binario* nodoAgregar, Nodo_Nivel* nivelActual, int x, int y, int grados);
    Nodo_Objeto* girar45(Nodo_Nivel* nodoActual, int size, int x, int y, int xInicialObjeto, int yInicialObjeto,int posX, int posY,
                  Lista_Puntos* listaActualPuntos, int veces, int &vezActual, int id, string objeto,
                  char letra, string color);
};

#endif // MENUEDITARNIVEL2_H
