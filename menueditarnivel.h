#ifndef MENUEDITARNIVEL_H
#define MENUEDITARNIVEL_H

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
#include <menueditarnivel2.h>

class menuEditarNivel
{
public:
    menuEditarNivel();
    void mostrarMenuEdicion(Arbol_AVL* proyecto, Arbol_Binario* arbolObjetos, int idProyecto);
    void eliminarNivelMenu(Lista_Niveles* listaNiveles, int idNivel);
};

#endif // MENUEDITARNIVEL_H
