#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H


#include "nodo_binario.h"
#include "lista_puntos.h"
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include "string.h"
using namespace std;

class Arbol_Binario
{
    private:
        Nodo_Binario* raiz;

        void Delete(Nodo_Binario* raiz);
        Nodo_Binario* insertar(Nodo_Binario* raiz, int id, string nombre, char letra, string color, Lista_Puntos *xy, Nodo_Binario* padre);

    public:
        Arbol_Binario();
        ~Arbol_Binario();

        Nodo_Binario* getRaiz();

        void insertar(int id, string nombre, char letra, string color, Lista_Puntos* xy);
        Nodo_Binario* getObjeto(int id, Nodo_Binario* raiz);

        void crearGrafica(string nombreProyecto, int idNivel);
        void crearGraficaRamas(ofstream &file, Nodo_Binario* raiz);

        void recorrerPreorden(Nodo_Binario* raiz);
        void recorrerInorden(Nodo_Binario* raiz);
        void recorrerPostorden(Nodo_Binario* raiz);
        //metodos eliminar
        void eliminarNodo(Nodo_Binario* raiz, int id);
        void eliminarNodoDeArbol(Nodo_Binario* raiz);
        void reemplazar(Nodo_Binario* nodoRemplazar, Nodo_Binario* nuevoNodo);
        Nodo_Binario* minimo(Nodo_Binario* raiz);
        void destruir(Nodo_Binario* raizEliminar);
        Arbol_Binario* copiarEsteArbolPreOrden();
        void llenarArbolCopiado(Nodo_Binario* raiz, Arbol_Binario* nuevoArbol);
};

#endif // ARBOL_BINARIO_H
