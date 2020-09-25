#include "arbol_binario.h"

Arbol_Binario::Arbol_Binario()
{
    this->raiz = NULL;
}

Arbol_Binario::~Arbol_Binario(){
    Delete(this->raiz);
}


void Arbol_Binario::Delete(Nodo_Binario *raiz){
    if(raiz==NULL){return;}
    if(raiz->getIzquierda() != NULL){
        Delete(raiz->getIzquierda());
    }
    if(raiz->getDerecha() != NULL){
        Delete(raiz->getDerecha());
    }
    raiz->getListaPuntos()->~Lista_Puntos();
    raiz->setIzquierda(NULL);
    raiz->setDerecha(NULL);
    delete raiz;
    raiz = NULL;
}

Nodo_Binario* Arbol_Binario::getObjeto(int id, Nodo_Binario* raiz){
    Nodo_Binario* actual = NULL;

    if(raiz->getIzquierda() != NULL){
        if(actual == NULL){
            actual = getObjeto(id, raiz->getIzquierda());
        }
    }

    if(raiz->getDerecha() != NULL){
        if(actual == NULL){
            actual = getObjeto(id, raiz->getDerecha());
        }
    }

    if(id == raiz->getId()){
        return raiz;
    } else {
        return actual;
    }
}

Nodo_Binario* Arbol_Binario::getRaiz(){
    return this->raiz;
}

Nodo_Binario* Arbol_Binario::insertar(Nodo_Binario* raiz, int id, string nombre, char letra, string color, Lista_Puntos* xy, Nodo_Binario* padre){
    if(raiz==NULL){
        raiz = new Nodo_Binario(id, nombre, letra, color, xy, padre);
        raiz->setDerecha(NULL);
        raiz->setIzquierda(NULL);
    } else if(id<raiz->getId()){
        Nodo_Binario* izq = insertar(raiz->getIzquierda(), id, nombre, letra, color, xy, raiz);
        //izq->setIzquierda(NULL);
        //izq->setDerecha(NULL);
        if(izq->getId() != raiz->getId()){
            raiz->setIzquierda(izq);
        }
    } else if(id>raiz->getId()){
        Nodo_Binario* der = insertar(raiz->getDerecha(), id, nombre, letra, color, xy, raiz);
        //der->setIzquierda(NULL);
        //der->setDerecha(NULL);
        if(der->getId() != raiz->getId()){
            raiz->setDerecha(der);
        }
    } else if(id == raiz->getId()){
        raiz->setId(id);
        raiz->setName(nombre);
        raiz->setLetra(letra);
        raiz->setColor(color);
        raiz->setListaPuntos(xy);
        raiz->setPadre(padre);
    }
    return raiz;
}

void Arbol_Binario::recorrerPostorden(Nodo_Binario *raiz){

    if(raiz->getIzquierda() != NULL){
        recorrerPostorden(raiz->getIzquierda());
    }
    if(raiz->getDerecha() != NULL){
        recorrerPostorden(raiz->getDerecha());
    }

    cout << "Dato: " << raiz->getId() << endl;
}

void Arbol_Binario::recorrerPreorden(Nodo_Binario *raiz){

    cout << "Dato: " << raiz->getId() << endl;

    if(raiz->getIzquierda() != NULL){
        recorrerPreorden(raiz->getIzquierda());
    }
    if(raiz->getDerecha() != NULL){
        recorrerPreorden(raiz->getDerecha());
    }
}

void Arbol_Binario::recorrerInorden(Nodo_Binario* raiz){

    if(raiz == NULL){
        return;
    }

    recorrerInorden(raiz->getIzquierda());
    cout << "* " << raiz->getId() << ". " << raiz->getName()
         << "#X: " << raiz->getListaPuntos()->getSizeX() << "#Y: " << raiz->getListaPuntos()->getSizeY() << endl;;
    recorrerInorden(raiz->getDerecha());

}

Arbol_Binario* Arbol_Binario::copiarEsteArbolPreOrden(){
    Arbol_Binario* nuevoArbol = new Arbol_Binario();
    Nodo_Binario* raiz = this->getRaiz();

    nuevoArbol->insertar(raiz->getId(), raiz->getName(), raiz->getLetra(), raiz->getColor(), raiz->getListaPuntos()->copiarEstaLista());

    nuevoArbol->llenarArbolCopiado(raiz, nuevoArbol);

    return nuevoArbol;
}

void Arbol_Binario::llenarArbolCopiado(Nodo_Binario* raiz, Arbol_Binario* nuevoArbol){

    if(raiz == NULL){
        return;
    }

    //Nodo_Binario* nuevo = new Nodo_Binario(raiz->getId(), raiz->getName(), raiz->getLetra(), raiz->getColor(), raiz->getListaPuntos()->copiarEstaLista(), NULL);
    nuevoArbol->insertar(nuevoArbol->getRaiz(), raiz->getId(), raiz->getName(), raiz->getLetra(), raiz->getColor(), raiz->getListaPuntos()->copiarEstaLista(), NULL);

    if(raiz->getIzquierda()!=NULL){
        llenarArbolCopiado(raiz->getIzquierda(), nuevoArbol);
    }
    if(raiz->getDerecha()!=NULL){
        llenarArbolCopiado(raiz->getDerecha(), nuevoArbol);
    }
}


void Arbol_Binario::insertar(int id, string nombre, char letra, string color, Lista_Puntos* xy){
    this->raiz=insertar(this->getRaiz(), id, nombre, letra, color, xy, NULL);
}

void Arbol_Binario::crearGrafica(string nombreProyecto, int idNivel){
    Nodo_Binario* aux = this->getRaiz();

    string nombreArchivo = nombreProyecto + "_Nivel_" + to_string(idNivel) + "_ABB" + ".gv";
    string nombreGrafica = nombreProyecto + "_Nivel_" + to_string(idNivel) + "_ABB" + ".ps";

    cout << "ARBOL BINARIO" << endl;
    ofstream MyFile(nombreArchivo);
    MyFile << "digraph G {";
    MyFile << "\n";
    MyFile << "rankdir = TB; \n";
    MyFile << "node [shape=record, width=.1, height=.1]; \n";


    if(this->getRaiz()->getDerecha() == NULL && this->getRaiz()->getIzquierda() == NULL){
        MyFile << "Objeto_" << aux->getName() << aux->getId() << "; \n";
    } else {
        try {
            crearGraficaRamas(MyFile, aux);
        } catch (exception e) {
            cout << e.what() << endl;
        }
    }

    cout << "Done";
    MyFile << "}";
    MyFile.close();
    try {
        cout << "Creating" << endl;
        system(("dot -Tps " + nombreArchivo + " -o " + nombreGrafica).c_str());
    } catch (exception e) {
        cout << "Oscar error occurred" << endl;
    }

}

void Arbol_Binario::crearGraficaRamas(ofstream &file, Nodo_Binario* aux){

    cout << "CodigoNodo: " << aux->getId() << endl;

    if(aux->getIzquierda() != NULL){
        file << "Objeto_" << aux->getName() << "_id_"  << aux->getId() << "->" << "Objeto_" << aux->getIzquierda()->getName() << "_id_" << aux->getIzquierda()->getId() << "; \n";
        crearGraficaRamas(file, aux->getIzquierda());
    }

    if(aux->getDerecha() != NULL){
        file << "Objeto_" << aux->getName() << "_id_"  << aux->getId() << "->" << "Objeto_" << aux->getDerecha()->getName() << "_id_" << aux->getDerecha()->getId() <<  "; \n";
        crearGraficaRamas(file, aux->getDerecha());
    }
}

//Funciones para EliminarNodoDeArbolBinario

void Arbol_Binario::eliminarNodo(Nodo_Binario* raiz, int id){
    if(this->getRaiz() == NULL){
        return;
    }
    else if(id < raiz->getId()){
        eliminarNodo(raiz->getIzquierda(), id);
    }
    else if(id > raiz->getId()){
        eliminarNodo(raiz->getDerecha(), id);
    }
    else if (id == raiz->getId()){
        eliminarNodoDeArbol(raiz);
    }
}

void Arbol_Binario::eliminarNodoDeArbol(Nodo_Binario *raizEliminar){
    if(raizEliminar->getIzquierda() && raizEliminar->getDerecha()){ //Si nodo tiene izq & der
        Nodo_Binario* menor = minimo(raizEliminar);
        raizEliminar->setId(menor->getId());
        raizEliminar->setName(menor->getName());
        raizEliminar->setColor(menor->getColor());
        raizEliminar->setLetra(menor->getLetra());
        raizEliminar->setListaPuntos(menor->getListaPuntos());

        eliminarNodoDeArbol(menor);
    }
    else if(raizEliminar->getIzquierda()){
        reemplazar(raizEliminar, raizEliminar->getIzquierda());
        destruir(raizEliminar);
    } else if (raizEliminar->getDerecha()){
        reemplazar(raizEliminar, raizEliminar->getDerecha());
        destruir(raizEliminar);
    } else{
        reemplazar(raizEliminar, NULL);
        destruir(raizEliminar);
    }
}

//Funcion Determina nodo mas izquierdo
Nodo_Binario* Arbol_Binario::minimo(Nodo_Binario* raiz){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->getIzquierda()){
        return minimo(raiz->getIzquierda());
    }
    else {
        return raiz;
    }
}

void Arbol_Binario::reemplazar(Nodo_Binario* nodoRemplazar, Nodo_Binario* nuevoNodo){
    if(nodoRemplazar->getPadre()){
        if(nodoRemplazar->getPadre()->getIzquierda() != NULL && nodoRemplazar->getId() == nodoRemplazar->getPadre()->getIzquierda()->getId()){
            nodoRemplazar->getPadre()->setIzquierda(nuevoNodo);
        }
        else if(nodoRemplazar->getId() == nodoRemplazar->getPadre()->getDerecha()->getId()){
            nodoRemplazar->getPadre()->setDerecha(nuevoNodo);
        }
    }
    if(nuevoNodo){
        //asignar padre
        nuevoNodo->setPadre(nodoRemplazar->getPadre());

    }
}

void Arbol_Binario::destruir(Nodo_Binario *raizEliminar){
    raizEliminar->setIzquierda(NULL);
    raizEliminar->setDerecha(NULL);
    delete raizEliminar;
}

