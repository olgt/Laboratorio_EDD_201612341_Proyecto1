#include "cargadorreportes.h"

cargadorReportes::cargadorReportes(Arbol_AVL* arbolProyectos, Arbol_Binario* arbolObjetos)
{
    this->arbolObjetos = arbolObjetos;
    this->proyectos = arbolProyectos;
}

void cargadorReportes::mostrarOpciones(){

    bool isContinue = true;
    int opcion = 0;

    while(isContinue != false){
        imprimirEspacios(10);
        imprimirOpciones();

        cout << "Escoja su opcion: ";

        cin >> opcion;

        if(opcion == 1){
            imprimirEspacios(5);

            reporteProyectoMayorNumeroNivelesAscendente();

            imprimirEspacios(5);
        }
        if(opcion == 2){
            reporteProyectoMayorNumeroNivelesDescendente();
            imprimirEspacios(5);
        }
        if(opcion == 3){
            imprimirEspacios(5);

            reporteProyectoNivelesPorObjeto();

            imprimirEspacios(5);
        }
        if(opcion == 4){
            imprimirEspacios(5);

            reporteNivelMasEspacio();

            imprimirEspacios(5);

        }
        if(opcion == 5){
            imprimirEspacios(5);

            reporteNivelMenosParedes();


            imprimirEspacios(5);

        }
        if(opcion == 6){
            imprimirEspacios(5);

            reporteNivelMasParedes();

            imprimirEspacios(5);

        }
        if(opcion == 7){
            imprimirEspacios(5);

            reporteNivelMasEspacioMasVentanas();

            imprimirEspacios(5);

        }
        if(opcion == 8){
            imprimirEspacios(5);

            reporteNivelMasEspacioMenosVentanas();

            imprimirEspacios(5);

        }
        if(opcion == 9){
            isContinue = false;
        }
     }

}



void cargadorReportes::reporteProyectoMayorNumeroNivelesDescendente(){
    this->proyectos->llenarArrayProyectosNiveles(this->proyectos->getRaiz(), "Descendente");
}
void cargadorReportes::reporteProyectoMayorNumeroNivelesAscendente(){
    this->proyectos->llenarArrayProyectosNiveles(this->proyectos->getRaiz(), "Ascendente");
}
void cargadorReportes::reporteProyectoNivelesPorObjeto(){
    if(this->proyectos != NULL){
        proyectos->recorrerArbol(proyectos->getRaiz());
        int a;
        cout << "Ingrese id de proyecto: ";
        cin >> a;
        NodoArbol* aux = proyectos->getProyecto(a, proyectos->getRaiz());
        Lista_Niveles* nivelesProyectoActual = aux->getListaNiveles();

        nivelesProyectoActual->nivelesPorNumeroDeObjetos();

    } else {
        cout << "No Hay Proyectos Guardados" << endl;
    }

}
void cargadorReportes::reporteNivelMasEspacio(){
    if(this->proyectos != NULL){
        proyectos->recorrerArbol(proyectos->getRaiz());
        int a;
        cout << "Ingrese id de proyecto: ";
        cin >> a;
        NodoArbol* aux = proyectos->getProyecto(a, proyectos->getRaiz());
        Lista_Niveles* nivelesProyectoActual = aux->getListaNiveles();
        Nodo_Nivel* nivelConMasEspacio = nivelesProyectoActual->nivelConMasEspacio();

        cout << endl << "El Nivel con Mas Espacio es: Nivel" << nivelConMasEspacio->getId();

    } else {
        cout << "No Hay Proyectos Guardados" << endl;
    }

}

void cargadorReportes::reporteNivelMasParedes(){
    if(this->proyectos != NULL){
        proyectos->recorrerArbol(proyectos->getRaiz());
        int a;
        cout << "Ingrese id de proyecto: ";
        cin >> a;
        NodoArbol* aux = proyectos->getProyecto(a, proyectos->getRaiz());
        Lista_Niveles* nivelesProyectoActual = aux->getListaNiveles();
        Nodo_Nivel* nivelConMasParedes = nivelesProyectoActual->nivelConMasParedes();

        cout << endl << "El Nivel con Mas Paredes es: Nivel" << nivelConMasParedes->getId();

    } else {
        cout << "No Hay Proyectos Guardados" << endl;
    }

}
void cargadorReportes::reporteNivelMenosParedes(){
    if(this->proyectos != NULL){
        proyectos->recorrerArbol(proyectos->getRaiz());
        int a;
        cout << "Ingrese id de proyecto: ";
        cin >> a;
        NodoArbol* aux = proyectos->getProyecto(a, proyectos->getRaiz());
        Lista_Niveles* nivelesProyectoActual = aux->getListaNiveles();
        Nodo_Nivel* nivelConMenosParedes = nivelesProyectoActual->nivelConMenosParedes();

        cout << endl << "El Nivel con Mas Paredes es: Nivel" << nivelConMenosParedes->getId();

    } else {
        cout << "No Hay Proyectos Guardados" << endl;
    }


}
void cargadorReportes::reporteNivelMasEspacioMasVentanas(){
    if(this->proyectos != NULL){
        proyectos->recorrerArbol(proyectos->getRaiz());
        int a;
        cout << "Ingrese id de proyecto: ";
        cin >> a;
        NodoArbol* aux = proyectos->getProyecto(a, proyectos->getRaiz());
        Lista_Niveles* nivelesProyectoActual = aux->getListaNiveles();
        Nodo_Nivel* nivelConMasEspacioMasVentanas = nivelesProyectoActual->nivelConMasEspacioMasVentanas();

        cout << endl << "El Nivel con mas espacio y ventanas es: Nivel" << nivelConMasEspacioMasVentanas->getId();

    } else {
        cout << "No Hay Proyectos Guardados" << endl;
    }

}
void cargadorReportes::reporteNivelMasEspacioMenosVentanas(){
    if(this->proyectos != NULL){
        proyectos->recorrerArbol(proyectos->getRaiz());
        int a;
        cout << "Ingrese id de proyecto: ";
        cin >> a;
        NodoArbol* aux = proyectos->getProyecto(a, proyectos->getRaiz());
        Lista_Niveles* nivelesProyectoActual = aux->getListaNiveles();
        Nodo_Nivel* nivelConMasEspacioMenosVentanas = nivelesProyectoActual->nivelConMasEspacioMenosVentanas();

        cout << endl << "El Nivel con mas espacio y ventanas es: Nivel" << nivelConMasEspacioMenosVentanas->getId();
    } else {
        cout << "No Hay Proyectos Guardados" << endl;
    }
}

void cargadorReportes::imprimirOpciones(){
    string opciones[] = {"8.1. Proyectos #Niveles Ascendente", "8.2. Proyectos #Niveles Descendente",
                         "8.3. Proyecto - Niveles Por Objeto (Menor a Mayor)", "8.4. Proyecto - Nivel con mas Espacio",
                         "8.5. Proyecto - Nivel con menos paredes", "8.6 Proyecto - Nivel con mas paredes",
                        "8.7 Proyecto - Nivel con mas Espacio y Mas Ventanas", "8.8 Proyecto - Nivel con mas Espacio y Menos ventanas",
                        "8.9 Salir"};

    for(int i = 0; i < 9 ; i++){
        cout << opciones[i] << endl;
    }


}
