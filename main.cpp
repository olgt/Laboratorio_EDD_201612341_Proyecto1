#include <QCoreApplication>

#include <menuPrincipal.h>

#include <iostream>
#include "Matriz.h"
#include "Nodo_Matriz.h"
#include "Cabecera.h"
#include "Nodo_Objeto.h"
#include "Arbol_AVL.h"
#include "nodoarbol.h"
#include "arbol_binario.h"
#include "lista_puntos.h"
#include "Nodo_Objeto.h"

using namespace std;

MenuPrincipal nuevoMenuPrincipal;

int main()
{
    nuevoMenuPrincipal.imprimirMenu();


    Matriz* nuevaMatriz = new Matriz();

    Nodo_Objeto* a = new Nodo_Objeto(1, "1", 'a', "white", 1, 2);
    Nodo_Objeto* c = new Nodo_Objeto(3, "3", 'a', "White", 1, 3);
    Nodo_Objeto* b = new Nodo_Objeto(2, "2", 'a', "white", 2, 1);
    Nodo_Objeto* d = new Nodo_Objeto(4, "4", 'a', "white", 2, 4);
    Nodo_Objeto* e = new Nodo_Objeto(5, "5", 'a', "white", 3, 5);
    Nodo_Objeto* f = new Nodo_Objeto(6, "6", 'a', "white", 1, 4);
    Nodo_Objeto* g = new Nodo_Objeto(7, "7", 'a', "white", 2, 1);
    Nodo_Objeto* h = new Nodo_Objeto(8, "8", 'a', "white", 3, 1);
    Nodo_Objeto* i = new Nodo_Objeto(9, "9", 'a', "white", 2, 2);
    Nodo_Objeto* j = new Nodo_Objeto(10, "10", 'a', "white", 3, 3);
    Nodo_Objeto* k = new Nodo_Objeto(11, "11", 'a', "white", 4, 3);
    Nodo_Objeto* k1 = new Nodo_Objeto(12, "12", 'a', "white", 5, 6);
    Nodo_Objeto* k2 = new Nodo_Objeto(13, "13", 'a', "white", 6, 2);
    Nodo_Objeto* k3 = new Nodo_Objeto(14, "14", 'a', "white", 0, 2);
    Nodo_Objeto* k4 = new Nodo_Objeto(15, "15", 'a', "white", 0, 0);
    Nodo_Objeto* k5 = new Nodo_Objeto(16, "16", 'a', "white", 2, 0);

    nuevaMatriz->add(a);
    nuevaMatriz->add(b);
    nuevaMatriz->add(c);
    nuevaMatriz->add(d);
    nuevaMatriz->add(e);
    nuevaMatriz->add(f);
    nuevaMatriz->add(g);
    nuevaMatriz->add(h);
    nuevaMatriz->add(i);
    nuevaMatriz->add(j);
    nuevaMatriz->add(k);
    nuevaMatriz->add(k1);
    nuevaMatriz->add(k2);
    nuevaMatriz->add(k3);
    nuevaMatriz->add(k4);
    nuevaMatriz->add(k5);



    nuevaMatriz->imprimirCabeceraX();
    nuevaMatriz->imprimirCabeceraY();
    imprimirEspacios(10);

    nuevaMatriz->crearGrafica("AAAAAGRAFICA");
    cout << "exito";


//    cout << ((Nodo_Objeto*)h->getDerecha())->getId();


/*
    Arbol_AVL *nuevo = new Arbol_AVL();
    Arbol_Binario* nuevobinario = new Arbol_Binario();
    int cantidad =0;

    Lista_Niveles* listaNiveles = new Lista_Niveles();
    Lista_Niveles* listaNiveles2 = new Lista_Niveles();;
    Lista_Niveles* listaNiveles3 = new Lista_Niveles();;
    Lista_Niveles* listaNiveles4 = new Lista_Niveles();;
    Matriz* nuevaMatriz = new Matriz();
    Nodo_Nivel* nuevoNivel = new Nodo_Nivel(1, nuevaMatriz, nuevobinario);
    Nodo_Nivel* nuevoNivel2 = new Nodo_Nivel(2, nuevaMatriz, nuevobinario);
    Nodo_Nivel* nuevoNivel3 = new Nodo_Nivel(3, nuevaMatriz, nuevobinario);
    Nodo_Nivel* nuevoNivel4 = new Nodo_Nivel(4, nuevaMatriz, nuevobinario);

    listaNiveles->addNode(nuevoNivel);
    listaNiveles->addNode(nuevoNivel2);
    listaNiveles2->addNode(nuevoNivel);
    listaNiveles3->addNode(nuevoNivel);
    listaNiveles4->addNode(nuevoNivel2);
    listaNiveles4->addNode(nuevoNivel4);
    listaNiveles4->addNode(nuevoNivel);
    //listaNiveles4->addNode(nuevoNivel3);



    nuevo->insertar("hola", listaNiveles, 1, nuevobinario); //420
    nuevo->insertar("que", listaNiveles4, 2, nuevobinario); //331
    nuevo->insertar("yes", listaNiveles, 3, nuevobinario); //337

    nuevo->insertar("no", listaNiveles4, 4, nuevobinario); //231
    nuevo->insertar("tri", listaNiveles, 5, nuevobinario); //335
    nuevo->insertar("tra", listaNiveles, 6, nuevobinario);//327

    nuevo->insertar("cuatro", listaNiveles2, 7, nuevobinario);//654
    nuevo->insertar("cuat", listaNiveles4, 8, nuevobinario);//543

    nuevo->crearGrafica();
    nuevo->recorrerArbol(nuevo->getRaiz());
    cantidad = nuevo->getCantidadNodos(cantidad, nuevo->getRaiz());
    cout <<  endl << "********************CANTIDAD: " << cantidad << endl;
    nuevo->llenarArrayProyectosNiveles(nuevo->getRaiz(), "Descendente");
    cout << endl;
    nuevo->llenarArrayProyectosNiveles(nuevo->getRaiz(), "Ascendente");
*/

    /*
    Lista_Puntos* nuevaLista = new Lista_Puntos();

    nuevobinario->insertar(4, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(6, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(2, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(3, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(1, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(0, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(10, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(8, "hola", 'a', "negro", nuevaLista);
    nuevobinario->insertar(9, "hola", 'a', "negro", nuevaLista);

    nuevobinario->eliminarNodo(nuevobinario->getRaiz(), 8);
    nuevobinario->crearGrafica();
    */

    return 0;
}
