#include "cargador_save.h"

Cargador_Save::Cargador_Save(Arbol_AVL* arbolProyectos, Arbol_Binario* arbolObjetos)
{

    this->arbolObjetos = arbolObjetos;
    this->arbolProyectos = arbolProyectos;
}

void Cargador_Save::guardarProyectos(){
    string MyFile = "{"
                    "\"proyectos\": [";
    int pos = 0;

    NodoArbol* actualProyecto = this->arbolProyectos->getRaiz();

    recorrerArbol(actualProyecto, MyFile, pos);
    cout << MyFile;

    MyFile = MyFile + "]}";
    ofstream out("Practica.json");
    out << MyFile;
    out.close();

}

void Cargador_Save::recorrerArbol(NodoArbol *raiz, string &MyFile, int &pos){

    if(this->arbolProyectos == NULL){
        imprimirEspacios(20);
        cout << "No hay proyectos guardados";
        imprimirEspacios(5);
    }
    else {
        if(raiz->getIzquierda() != NULL){
            recorrerArbol(raiz->getIzquierda(), MyFile, pos);
        }

        if(raiz->getDerecha() != NULL){
            recorrerArbol(raiz->getDerecha(), MyFile, pos);
        }

        string nombreProyecto = raiz->getName();

        MyFile = MyFile + "{ \"nombre\": \"" + nombreProyecto + "\",";
        guardarListaNiveles(MyFile, raiz);
        MyFile = MyFile + "}, ";

        pos++;

    }
}

void Cargador_Save::guardarListaNiveles(string &MyFile, NodoArbol* proyectoActual){

    Lista_Niveles* listaNivelesActual = proyectoActual->getListaNiveles();
    Nodo_Nivel* nivelActual = listaNivelesActual->getHead();

    MyFile = MyFile + "\"niveles\": [";

    while(nivelActual !=NULL){
        string numeroNivel = to_string(nivelActual->getId());
        MyFile = MyFile + "{ \"nivel\": " + numeroNivel + ",";

        guardarParedes(nivelActual, MyFile);
        guardarVentanas(nivelActual, MyFile);
        guardarObjetos(nivelActual, MyFile);
        MyFile = MyFile + "},";
        nivelActual=nivelActual->getSiguiente();
    }

    MyFile = MyFile + "],";


}

void Cargador_Save::guardarParedes(Nodo_Nivel * nodoNivel, string &MyFile){

    Matriz* matrizActual = nodoNivel->getMatriz();


    MyFile = MyFile + "\"paredes\" :[";



    MyFile = MyFile + "],";

}

void Cargador_Save::guardarVentanas(Nodo_Nivel * nodoNivel, string &MyFile){

    MyFile = MyFile + "\"ventanas\" :[";



    MyFile = MyFile + "],";
}

void Cargador_Save::guardarObjetos(Nodo_Nivel * nodoNivel, string &MyFile){

    MyFile = MyFile + "\"objetos\" :[";



    MyFile = MyFile + "]";
}


void Cargador_Save::guardarMatriz(string &MyFile){

}

void Cargador_Save::guardarArbolBinario(){

}
