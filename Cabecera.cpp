#include "Cabecera.h"

Cabecera::Cabecera(int nombre)
{
    this->nombre = nombre;

}

void Cabecera::setPos(int nombre){
    this->nombre = nombre;
}

int Cabecera::getPos(){
    return this->nombre;
}
