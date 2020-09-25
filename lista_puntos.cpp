#include "lista_puntos.h"

Lista_Puntos::Lista_Puntos()
{
    this->head = NULL;
    this->tail = NULL;

};

Lista_Puntos::~Lista_Puntos(){
    Delete(this->gethead());
}

void Lista_Puntos::Delete(Nodo_Puntos* raiz){
    Nodo_Puntos* actual = raiz;
    Nodo_Puntos* next= raiz->getSiguiente();
    while(actual != NULL){
        delete actual;
        actual = NULL;
        if(next != NULL){
            next = next->getSiguiente();
        }
    }
}

void Lista_Puntos::addNode(Nodo_Puntos *nuevo){
    if(this->head == NULL){
        this->head = nuevo;
        this->tail = nuevo;
    } else {
        this->tail->setSiguiente(nuevo);
        this->tail = nuevo;
    }
    //printLinkedList();

}

/*void Lista_Puntos::searchNode(int id){
    Nodo_Puntos *aux = this->head;
    while(aux != NULL){
        if(aux->getId() == id){
            cout << "Nodos Encontrados: " << endl;
            cout << aux->getName();
            cout << ",";
        }
        aux = aux->getSiguiente();
    }
}*/

void Lista_Puntos::deleteNode(int x, int y){
    Nodo_Puntos *aux = this->head;
    Nodo_Puntos *temp = this->head;
    while(aux != NULL){
        if(aux->getX() == x && aux->getY() == y){
            if(aux == this->head){
                this->head = this->head->getSiguiente();
            } else if (aux == this->tail){
                temp->setSiguiente(NULL);
                this->tail = temp;
            }
            else{
                temp->setSiguiente(aux->getSiguiente());
            }
        }
        aux = aux->getSiguiente();
        if(temp != aux && temp->getSiguiente() != aux){
            temp = temp->getSiguiente();
        }
    }
}

int Lista_Puntos::getSizeNodos(){
    Nodo_Puntos* punto = this->gethead();
    int size = 0;
    while(punto != NULL){
        size++;
        punto = punto->getSiguiente();
    }
    return size;
}

int Lista_Puntos::getSizeX(){
    Nodo_Puntos* punto = this->gethead();
    int x = 0;

    while(punto->getSiguiente() != NULL){
        if(punto->getX() != punto->getSiguiente()->getX()){
            x++;
        }
        punto = punto->getSiguiente();
    }
    if(punto->getSiguiente() == NULL){
            x++;
    }
    return x;
}

int Lista_Puntos::getSizeY(){
    Nodo_Puntos* punto = this->gethead();
    int y = 0;

    while(punto->getSiguiente() != NULL){
        if(punto->getY() != punto->getSiguiente()->getY()){
            y++;
        }
        punto = punto->getSiguiente();
    }
    if(punto->getSiguiente()==NULL){
        y++;
    }
    return y;
}

Nodo_Puntos* Lista_Puntos::gethead(){
    return this->head;
}

Nodo_Puntos* Lista_Puntos::getPunto(int pos){
    int i = 0;

    Nodo_Puntos* punto = this->gethead();

    while(i != pos){
        i++;
        punto = punto->getSiguiente();
    }
    return punto;

}

Lista_Puntos* Lista_Puntos::copiarEstaLista(){
    Lista_Puntos* nuevaListaPuntos = new Lista_Puntos();

    Nodo_Puntos* actual = this->head;

    while(actual!= NULL){
        int x = actual->getX();
        int y = actual->getY();

        Nodo_Puntos* nodoIngresa = new Nodo_Puntos(x, y);
        nuevaListaPuntos->addNode(nodoIngresa);

        actual = actual->getSiguiente();
    }
    return nuevaListaPuntos;
}
