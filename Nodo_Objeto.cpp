#include "Nodo_Objeto.h"

Nodo_Objeto::Nodo_Objeto(int id, string objeto, char letra, string color, int x, int y)
{
    this->id = id;
    this->letra = letra;
    this->color = color;
    this->x = x;
    this->y = y;
    this->objeto = objeto;

}

string Nodo_Objeto::getColor(){
    return this->color;
}

string Nodo_Objeto::getObjeto(){
    return this->objeto;
}

void Nodo_Objeto::setObjeto(string objeto){
    this->objeto = objeto;
}


void Nodo_Objeto::setX(int x){
    this->x = x;

}

int Nodo_Objeto::getX(){
    return this->x;
}

void Nodo_Objeto::setY(int y){
    this->y = y;
}

int Nodo_Objeto::getY(){
    return this->y;
}

int Nodo_Objeto::getId(){
    return this->id;
}

void Nodo_Objeto::setLetra(char letra){
    this->letra = letra;
}
void Nodo_Objeto::setColor(string color){
    this->color = color;
}
void Nodo_Objeto::setId(int id){
    this->id = id;
}

char Nodo_Objeto::getLetra(){
    return this->letra;
}

string Nodo_Objeto::getXY(){
    int x = this->getX();
    int y = this->getY();
    string XY = to_string(x) + to_string(y);
    return XY;

}
