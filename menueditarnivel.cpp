#include "menueditarnivel.h"

menuEditarNivel::menuEditarNivel()
{

}

void menuEditarNivel::mostrarMenuEdicion(Arbol_AVL* arbolProyectos, Arbol_Binario* arbolObjetos, int idProyecto){

    NodoArbol* proyectoActual = arbolProyectos->getProyecto(idProyecto, arbolProyectos->getRaiz());
    Lista_Niveles* listaNivelesActual = proyectoActual->getListaNiveles();
    string opciones[] = {"2.1. Agregar Nivel", "2.2. Editar Nivel", "2.3. Eliminar Nivel",
                         "2.4. Eliminar Proyecto", "2.5. Salir"};

    bool isContinue = true;
    int opcion = 0;

    while(isContinue != false){
        imprimirEncabezado();
        for(int i = 0; i < 5 ; i++){
            cout << opciones[i] << endl;
        }

        cout << "Escoja su opcion: ";

        cin >> opcion;

        if(opcion == 1){
            int idNivel;
            string nombreArchivo;
            Cargador_Proyectos cargador;

            listaNivelesActual->imprimirNiveles();

            cout << endl << "Ingrese nombre de archivo: ";
            cin >> nombreArchivo;

            cargador.agregarNivelExtra(listaNivelesActual, arbolObjetos, nombreArchivo);

            imprimirEspacios(10);
        }
        if(opcion == 2){
            menuEditarNivel2* nuevo = new menuEditarNivel2(proyectoActual, arbolObjetos, idProyecto);

            nuevo->mostrarNiveles();

            imprimirEspacios(10);
        }
        if(opcion == 3){
            int idNivel;

            listaNivelesActual->imprimirNiveles();

            cout << endl << "Ingrese Nivel a borrar: ";
            cin >> idNivel;

            string opcion;
            cout << endl << "Eliminar Proyecto? (Y/N): ";
            cin >> opcion;

            if(opcion == "Y" || opcion == "y"){
                eliminarNivelMenu(listaNivelesActual,idNivel);
            } else {
                cout << "Opcion Cancelada";
            }
            imprimirEspacios(10);

        }
        if(opcion == 3){


            imprimirEspacios(10);

        }
        if(opcion == 5){
            isContinue = false;
        }
     }

}

void menuEditarNivel::eliminarNivelMenu(Lista_Niveles* listaNivelesActual,int idNivel){

    Nodo_Nivel* nodoAEliminar = listaNivelesActual->getNodo(idNivel);
    if(nodoAEliminar != NULL){
        listaNivelesActual->deleteNode(nodoAEliminar->getId());
        delete nodoAEliminar;
    }

}

