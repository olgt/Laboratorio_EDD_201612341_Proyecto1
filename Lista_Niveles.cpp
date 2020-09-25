#include "Lista_Niveles.h"

Lista_Niveles::Lista_Niveles()
{
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

Lista_Niveles::~Lista_Niveles(){
    Delete(this->getHead());
}

void Lista_Niveles::Delete(Nodo_Nivel* raiz){
    Nodo_Nivel* actual = raiz;
    Nodo_Nivel* next= raiz->getSiguiente();
    while(actual != NULL){
        delete actual;
        actual = NULL;
        if(next != NULL){
            next = next->getSiguiente();
        }
    }
}

void Lista_Niveles::addNode(Nodo_Nivel *nuevo){
    Nodo_Nivel* nodoEncontrado = getNodo(nuevo->getId());
    if(this->head == NULL){
        this->head = nuevo;
        this->tail = nuevo;
        this->size++;
    } else if(nodoEncontrado == NULL){
        this->tail->setSiguiente(nuevo);
        this->tail->getSiguiente()->setAnterior(this->tail);
        this->tail = nuevo;
        this->size++;
    } else if(nodoEncontrado != NULL){
        deleteNode(nodoEncontrado->getId());
        nodoEncontrado->~Nodo_Nivel();
        this->tail->setSiguiente(nuevo);
        this->tail->getSiguiente()->setAnterior(this->tail);
        this->tail = nuevo;
    }
}

Nodo_Nivel* Lista_Niveles::getNodo(int id){
    Nodo_Nivel* actual = this->head;

    while(actual != NULL){
        if(actual->getId() == id){
            return actual;
        }
        actual = actual->getSiguiente();
    }

    return NULL;
}

void Lista_Niveles::searchNode(int id)
{
    Nodo_Nivel *aux = this->head;
        while(aux != NULL){
            if(aux->getId() == id){
                cout << "Nodos Encontrados: " << endl;
                cout << ",";
            }
            aux = aux->getSiguiente();
        }
}

void Lista_Niveles::deleteNode(int id){
    Nodo_Nivel *aux = this->head;
        while(aux != NULL){
            if(aux->getId() == id){
                if(aux == this->head){
                    if(aux->getSiguiente() == NULL){
                        this->head = NULL;
                        this->tail = NULL;
                    } else {
                        this->head = this->head->getSiguiente();
                        this->head->setAnterior(NULL);
                        if(this->head->getSiguiente() == NULL){
                            this->tail = this->head;
                        }
                    }
                } else if (aux == this->tail){
                    this->tail = aux->getAnterior();
                    this->tail->setSiguiente(NULL);
                }
                else{
                    aux->getAnterior()->setSiguiente(aux->getSiguiente());
                    aux->getSiguiente()->setAnterior(aux->getAnterior());
                }
            }

            aux = aux->getSiguiente();
         }
        this->size = size -1;
}

void Lista_Niveles::graficarNiveles(string nombreProyecto){
    Nodo_Nivel* actual = this->getHead();
    while(actual != NULL){
        string nombreNivel = "Proyecto_" + nombreProyecto + "_Nivel" + to_string(actual->getId());
        actual->getMatriz()->crearGrafica(nombreNivel);
        actual->getABB()->crearGrafica(nombreProyecto, actual->getId());
        actual = actual->getSiguiente();
    }
}

void Lista_Niveles::graficarTodosABB(string nombreProyecto){
    Nodo_Nivel* actual = this->getHead();
    while(actual != NULL){
        actual->getABB()->crearGrafica(nombreProyecto, actual->getId());
        actual = actual->getSiguiente();
    }
}

int Lista_Niveles::getSize(){
    return this->size;
}

Nodo_Nivel* Lista_Niveles::getHead(){
    return this->head;
}

Nodo_Nivel* Lista_Niveles::getTail(){
    return this->tail;
}

void Lista_Niveles::imprimirNiveles(){
    Nodo_Nivel* actual = this->head;

    while(actual!=NULL){
        cout << "Nivel: " << actual->getId() << endl;
        actual = actual->getSiguiente();
    }
}

Nodo_Nivel* Lista_Niveles::nivelConMasEspacio(){
    Nodo_Nivel* aux = this->getHead();
    Nodo_Nivel* nodoConMasEspacio = aux;

    int actualNumero = aux->getMatriz()->getEspacio();

    while(aux != NULL){
        if(nodoConMasEspacio->getMatriz()->getEspacio() < actualNumero){
            nodoConMasEspacio = aux;
        }

        aux = aux->getSiguiente();
        if(aux!=NULL){
            actualNumero = aux->getMatriz()->getEspacio();
        }

    }
    return  nodoConMasEspacio;

}

Nodo_Nivel* Lista_Niveles::nivelConMasParedes(){
    int a = 0;
    Nodo_Nivel* aux = this->getHead();
    Nodo_Nivel* aux2 = this->getHead();
    Nodo_Nivel* nodoConMasParedes = aux;

    int actualNumero = aux->getMatriz()->getParedes();
    int actualSiguienteNumero = aux2->getMatriz()->getParedes();

    while(aux != NULL){
        if(nodoConMasParedes->getMatriz()->getParedes() < actualNumero){
            nodoConMasParedes = aux;
        }

        aux = aux->getSiguiente();
        if(aux!=NULL){
            actualNumero = aux->getMatriz()->getParedes();
        }

    }
    return  nodoConMasParedes;

}
Nodo_Nivel* Lista_Niveles::nivelConMenosParedes(){
    int a = 0;
    Nodo_Nivel* aux = this->getHead();
    Nodo_Nivel* aux2 = this->getHead();
    Nodo_Nivel* nodoConMenosParedes = aux;

    int actualNumero = aux->getMatriz()->getParedes();
    int actualSiguienteNumero = aux2->getMatriz()->getParedes();

    while(aux != NULL){
        if(nodoConMenosParedes->getMatriz()->getParedes() > actualNumero){
            nodoConMenosParedes = aux;
        }

        aux = aux->getSiguiente();
        if(aux != NULL){
            actualNumero = aux->getMatriz()->getParedes();
        }

    }
    return  nodoConMenosParedes;

}

Nodo_Nivel* Lista_Niveles::nivelConMasEspacioMenosVentanas(){
    Nodo_Nivel* aux = this->getHead();
    Nodo_Nivel* nodoConMasEspacio = aux;

    int auxNumeroEspacio = aux->getMatriz()->getEspacio();
    int auxNumeroVentanas = aux->getMatriz()->getVentanas();


    while(aux != NULL){
        if(nodoConMasEspacio->getMatriz()->getEspacio() < auxNumeroEspacio){
            if(nodoConMasEspacio->getMatriz()->getVentanas() < auxNumeroVentanas){
                nodoConMasEspacio = aux;
            }
        }

        aux = aux->getSiguiente();
        if(aux!=NULL){
            auxNumeroEspacio = aux->getMatriz()->getEspacio();
            auxNumeroVentanas = aux->getMatriz()->getVentanas();
        }

    }
    return  nodoConMasEspacio;
}

Nodo_Nivel* Lista_Niveles::nivelConMasEspacioMasVentanas(){
    Nodo_Nivel* aux = this->getHead();
    Nodo_Nivel* nodoConMasEspacio = aux;

    int auxNumeroEspacio = aux->getMatriz()->getEspacio();
    int auxNumeroVentanas = aux->getMatriz()->getVentanas();


    while(aux != NULL){
        if(nodoConMasEspacio->getMatriz()->getEspacio() < auxNumeroEspacio){
            if(nodoConMasEspacio->getMatriz()->getVentanas() > auxNumeroVentanas){
                nodoConMasEspacio = aux;
            }
        }

        aux = aux->getSiguiente();
        if(aux != NULL){
            auxNumeroEspacio = aux->getMatriz()->getEspacio();
            auxNumeroVentanas = aux->getMatriz()->getVentanas();
        }

    }
    return  nodoConMasEspacio;
}

void Lista_Niveles::nivelesPorNumeroDeObjetos(){
    llenarArrayProyectosNiveles();
}

void Lista_Niveles::aumentarObjetos(int cantidad){
    this->size = this->size + cantidad;
}

int ** Lista_Niveles::llenarArray(int ** proyectoArray, Nodo_Nivel* nodo_Actual, int &pos){
    if(this->getHead() == NULL){
        imprimirEspacios(20);
        cout << "No hay proyectos guardados";
        imprimirEspacios(5);
    }
    else {
        if(nodo_Actual->getSiguiente() != NULL){
            llenarArray(proyectoArray, nodo_Actual->getSiguiente(), pos);
        }
        proyectoArray[pos][0] = nodo_Actual->getId();
        proyectoArray[pos][1] = nodo_Actual->getMatriz()->getObjetos();

        pos++;
    }
    return proyectoArray;
}

int ** Lista_Niveles::llenarArrayProyectosNiveles(){
    int cantidad = 0;
    int pos = 0;
    int cantidadNiveles = this->getSize();

    int ** proyectoArray = 0;
    int **p;

    proyectoArray = new int*[cantidadNiveles];

    for(int i = 0; i < cantidadNiveles ; i++){
        proyectoArray[i] = new int[2];
    }


    p = llenarArray(proyectoArray, this->getHead(), pos);

    cout << "Ordenando" << endl;

    int aux;

    //Ordenamiento Burbuja
    for(int i = 0; i < (cantidadNiveles); i++){
        for(int j = 0; j< (cantidadNiveles-i-1); j++){
            if(p[j+1][1] < p[j][1]){
                aux = p[j+1][1];
                p[j+1][1]=p[j][1];
                p[j][1]=aux;

                aux = p[j+1][0];
                p[j+1][0]=p[j][0];
                p[j][0] = aux;
            }
        }
    }

    //Ascendente / Descendente
     for(int i = 0; i< cantidadNiveles; i++){
            int h = p[i][0];

            Nodo_Nivel* nivelActual = this->getNodo(h);

            if(nivelActual != NULL){
                cout << "Nivel " << nivelActual->getId() <<
                        " Cantidad Objetos: " << nivelActual->getMatriz()->getObjetos() << endl;

            }

    }


    return p;

}

