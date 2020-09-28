#include "Matriz.h"

Matriz::Matriz()
{
    this->horizontal = NULL;
    this->vertical = NULL;
    this->objetos = 0;
}

Matriz::~Matriz(){
    Nodo_Matriz *aux, *aux2, *tmp, *tmp2, *extra, *extra2;
//Estoy arreglando el constructor y luego probar cargar proyectos muchas veces para que no de error
    aux=this->vertical;
    tmp=this->horizontal;
    while(aux!=NULL){
        extra = aux->getAbajo();
        aux2 = aux->getDerecha();
        while(aux2!=NULL){
            extra2 = aux2->getDerecha();
            delete aux2;
            aux2 = NULL;
            aux2 = extra2;
        }
        delete aux;
        aux = NULL;
        aux = extra;
    }
    while(tmp!=NULL){
        tmp2 = tmp->getDerecha();
        delete tmp;
        tmp = NULL;
        tmp =  tmp2;
    }
    this->horizontal = NULL;
    this->vertical = NULL;
    this->objetos = 0;
}

Cabecera* Matriz::crearHorizontal(int y){
    if(this->horizontal == NULL){
        Cabecera* nueva = new Cabecera(y);
        this->horizontal = nueva;
        return nueva;
    }
    Cabecera* aux = this->horizontal;
    //cout << "Acutal: " << aux->getPos() << endl;;
    if(y == aux->getPos()){
         cout << "Caso requerido" << endl;
         Cabecera* nueva = new Cabecera(y);
         nueva->setDerecha(aux);
         this->horizontal->setIzquierda(nueva);
         this->horizontal = nueva;
         return nueva;
    }
    else if (y < aux->getPos()){
        Cabecera* nueva = new Cabecera(y);
        nueva->setDerecha(this->horizontal);
        this->horizontal->setIzquierda(nueva);
        this->horizontal = nueva;
        return nueva;
    }
    while(aux->getDerecha() != NULL){
        if(y <= aux->getPos() && y <= (((Cabecera*)aux->getDerecha())->getPos())){
            Cabecera* nueva =new Cabecera(y);
            Cabecera* tmp = (Cabecera*)aux->getDerecha();

            tmp->setIzquierda(nueva);
            nueva->setDerecha(tmp);
            aux->setDerecha(nueva);
            nueva->setIzquierda(aux);

            return nueva;
        }
        aux=(Cabecera*)aux->getDerecha();
    }

    Cabecera* nueva = new Cabecera(y);
    aux->setDerecha(nueva);
    nueva->setIzquierda(aux);
    return nueva;

}

Cabecera* Matriz::crearVertical(int x){
    if(this->vertical== NULL){
        Cabecera* nueva = new Cabecera(x);
        this->vertical = nueva;
        return nueva;
    }
    Cabecera* aux = this->vertical;
    if(x == aux->getPos()){
         Cabecera* nueva = new Cabecera(x);
         nueva->setAbajo(aux);
         this->vertical->setAbajo(nueva);
         this->vertical = nueva;
         return nueva;
    }
    else if( x < aux->getPos()){
        Cabecera* nueva = new Cabecera(x);
        nueva->setAbajo(this->vertical);
        this->vertical->setArriba(nueva);
        this->vertical = nueva;
        return nueva;
    }
    while(aux->getAbajo() != NULL){
        if(x <= aux->getPos() && x <= ((Cabecera*)aux->getAbajo())->getPos()){
            Cabecera* nueva =new Cabecera(x);
            Cabecera* tmp = (Cabecera*)aux->getAbajo();

            tmp->setArriba(nueva);
            nueva->setAbajo(tmp);
            aux->setAbajo(nueva);
            nueva->setArriba(aux);

            return nueva;
        }
        aux=(Cabecera*)aux->getAbajo();
    }

    Cabecera* nueva = new Cabecera(x);
    aux->setAbajo(nueva);
    nueva->setArriba(aux);

    return nueva;
}

Nodo_Matriz* Matriz::obtenerUltimoHorizontal(Cabecera* cabecera, int y){
    if(cabecera->getDerecha() == NULL){return cabecera;}
    Nodo_Matriz* aux = cabecera->getDerecha();

    while(aux->getDerecha() != NULL){
        if(y == (((Nodo_Objeto*)aux)->getY())){
               return aux;
        }
        else if(y < (((Nodo_Objeto*)aux)->getY())){
            return aux->getIzquierda();
        }
        aux=aux->getDerecha();
    }
    if(y < (((Nodo_Objeto*)aux)->getY())){
        return aux->getIzquierda();
    }
    return aux;
}

Nodo_Matriz* Matriz::obtenerUltimoVertical(Cabecera* cabecera, int x){
    if(cabecera->getAbajo() == NULL){return cabecera;}
    Nodo_Matriz* aux = cabecera->getAbajo();

    while(aux->getAbajo() != NULL){
        int xObjeto = ((Nodo_Objeto*)aux)->getX();
        if(x == ((Nodo_Objeto*)aux)->getX()){
               return aux;
        }
        else if( x < ((Nodo_Objeto*)aux)->getX()){ //error
            return aux->getArriba();
        }
        aux=aux->getAbajo();
    }
    if(x < ((Nodo_Objeto*)aux)->getX()){
        return aux->getArriba();
    }
    return aux;
}

Cabecera* Matriz::getVertical(int x){
    if(this->vertical == NULL){return NULL;}
    Cabecera* aux = this->vertical;
    while(aux != NULL){
        if(aux->getPos() == x){
            return aux;
        }
        aux = (Cabecera*)aux->getAbajo();
    }
    return NULL;
}

Cabecera* Matriz::getHorizontal(int y){
    if(this->vertical == NULL){return NULL;}
    Cabecera* aux = this->horizontal;
    while(aux != NULL){
        if(aux->getPos() == y){
            //cout << "Aux valor: " << aux->getPos() << endl;
            //cout << "Y valor: " << y << endl;
            return aux;
        }
        aux = (Cabecera*)aux->getDerecha();
    }
    return NULL;
}

void Matriz::add(Nodo_Objeto *nuevo){
    if(nuevo->getX() < 0 || nuevo->getY() < 0){
        cout << "Nodo Fuera de alcance" << endl;
    }
    else {
        Cabecera* vertical = this->getVertical(nuevo->getX());
        Cabecera* horizontal = this->getHorizontal(nuevo->getY());

        if(vertical == NULL){
            vertical = crearVertical(nuevo->getX());
        }
        if(horizontal == NULL){
            horizontal = crearHorizontal(nuevo->getY());
        }
        Nodo_Matriz *izquierda = this->obtenerUltimoHorizontal(vertical, nuevo->getY());
        Nodo_Matriz *superior = this->obtenerUltimoVertical(horizontal, nuevo->getX());

        int nodoNumeroIzquierdaX = ((Nodo_Objeto*)izquierda)->getX();
        int nodoNumeroIzquierdaY = ((Nodo_Objeto*)izquierda)->getY();
        int nodoNumeroSuperiorY = ((Nodo_Objeto*)superior)->getY();
        int nodoNumeroSuperiorX = ((Nodo_Objeto*)superior)->getX();

        bool izquierdaEsCabecera = chequearNodoEsCabecera(izquierda);
        bool superiorEsCabecera = chequearNodoEsCabecera(superior);
        //Problem
        if(nodoNumeroIzquierdaX == nuevo->getX() && nodoNumeroIzquierdaY == nuevo->getY()
                && nodoNumeroSuperiorY == nuevo->getY() && nodoNumeroSuperiorX == nuevo->getX()
                && !izquierdaEsCabecera && !superiorEsCabecera){
            ((Nodo_Objeto*)izquierda)->setObjeto(nuevo->getObjeto());
            ((Nodo_Objeto*)izquierda)->setLetra(nuevo->getLetra());
            ((Nodo_Objeto*)izquierda)->setColor(nuevo->getColor());
            ((Nodo_Objeto*)izquierda)->setId(nuevo->getId());

        } else {
            if(izquierda->getDerecha() == NULL){
                izquierda->setDerecha(nuevo);
                nuevo->setIzquierda(izquierda);
            }else{
                    Nodo_Matriz* tmp = izquierda->getDerecha();
                    izquierda->setDerecha(nuevo);
                    nuevo->setIzquierda(izquierda);
                    tmp->setIzquierda(nuevo);
                    nuevo->setDerecha(tmp);
            }
            if(superior->getAbajo()==NULL){

                superior->setAbajo(nuevo);
                nuevo->setArriba(superior);
            } else {
                    Nodo_Matriz* tmp = superior->getAbajo();
                    superior->setAbajo(nuevo);
                    nuevo->setArriba(superior);
                    tmp->setArriba(nuevo);
                    nuevo->setAbajo(tmp);
            }

        }

    }

}

bool Matriz::chequearNodoEsCabecera(Nodo_Matriz* nodoAnalizado){
    bool esCabecera = false;

    Nodo_Matriz* vertical = this->vertical;
    Nodo_Matriz* horizontal = this->horizontal;

    while(vertical!=NULL){
        if(vertical == nodoAnalizado){
            return true;
        }
        vertical = vertical->getAbajo();

    }
    while(horizontal!=NULL){
        if(horizontal == nodoAnalizado){
            return true;
        }

        horizontal = horizontal->getDerecha();
    }
    return esCabecera;
}


void Matriz::imprimirCabeceraX(){
    Nodo_Matriz* aux = this->vertical;
    while(aux != NULL){
        int pos = ((Cabecera*)aux)->getPos();
        cout << "Cabecera X: ";
        cout << pos;
        cout << ", ";
        aux = aux->getAbajo();
    }
    cout << endl;
}

void Matriz::imprimirCabeceraY(){
    Nodo_Matriz* aux = this->horizontal;
    while(aux != NULL){
        cout << "Cabecera Y: ";
        cout << ((Cabecera*)aux)->getPos();
        cout << ", ";
        aux = aux->getDerecha();
    }
}

void Matriz::imprimirMatriz(){
    Nodo_Matriz *aux = this->vertical;
    Nodo_Matriz *aux2 = this->vertical;

    while(aux2 != NULL){
        aux = aux->getDerecha();
        while(aux!=NULL){
            cout << ((Nodo_Objeto*)aux)->getObjeto();

            if(aux->getDerecha() == NULL){cout << "; \n";}
            else { cout << ", ";}

            aux = aux->getDerecha();
        }
        aux = aux2->getAbajo();
        aux2 = aux2->getAbajo();
    }
}

//Metodos crear Grafica

void Matriz::crearGrafica(string nombre){
    Nodo_Matriz *vertical = this->vertical;
    Nodo_Matriz *horizontal = this->horizontal;

    if(vertical != NULL && horizontal != NULL){
        Nodo_Matriz *aux = this->vertical;
        Nodo_Matriz *aux2 = this->vertical;

        Nodo_Matriz *tmpH = this->horizontal;
        Nodo_Matriz *tmpV = this->vertical;

        string nombreArchivo = "./Imagenes/" + nombre + ".gv";
        string nombreGrafica = "./Imagenes/" + nombre + ".ps";

            ofstream MyFile(nombreArchivo); //error?
            MyFile << "digraph G {";
            MyFile << "\n";
            MyFile << "rankdir = TB; \n";
            MyFile << "node [shape=box, width=.1, height=.1]; \n";
            MyFile << "node0 [label = \"Matriz\", group=-1] \n";

            //RANKS Nodos Cabecera Y
            MyFile << "{ \n";
            MyFile << "rank=same; ";
            MyFile << "node0, ";

            while(horizontal != NULL){
              MyFile << "nodeY" << ((Cabecera*)horizontal)->getPos();

              if(horizontal->getDerecha() == NULL){MyFile << "; \n";}
              else { MyFile << ", ";}

              horizontal = horizontal->getDerecha();
            }
            MyFile << "} \n";
            horizontal = this->horizontal;

              //RANKS Nodos Matris y Cabecera "Y" (Creamos Nodos)
              while(aux2 != NULL){
                  MyFile << "{ \n";
                  MyFile << "rank=same; ";
                  MyFile << "nodeX" << ((Cabecera*)aux)->getPos() << ", ";
                  aux = aux->getDerecha();

                  while(aux!=NULL){
                      MyFile << "node" << ((Nodo_Objeto*)aux)->getXY();
                      agregarNodosVaciosARank(MyFile, ((Nodo_Objeto*)aux)->getX());

                      if(aux->getDerecha() == NULL){MyFile << "; \n";}
                      else { MyFile << ", ";}

                      aux = aux->getDerecha();
                  }
                  aux = aux2->getAbajo();
                  aux2 = aux2->getAbajo();
                  MyFile << "} \n";

              }

              aux2 = this->vertical;
              aux = this->vertical;


              //NODOS CABECERA Groups
              while(horizontal != NULL){
                MyFile << "nodeY" << ((Cabecera*)horizontal)->getPos() << "[label = \"" << ((Cabecera*)horizontal)->getPos() << "\""
                       << ", group=" << ((Cabecera*)horizontal)->getPos() << "]; \n";
                horizontal = horizontal->getDerecha();
              }
              while(vertical != NULL){
                  MyFile << "nodeX" << ((Cabecera*)vertical)->getPos()  << "[label = \"" << ((Cabecera*)vertical)->getPos()
                         << "\""  << ", group=-1" << "]; \n";
                  vertical = vertical->getAbajo();
              }

              //creamosNodos vacios
              crearNodosExtraMatrizHorizontal(MyFile, this->horizontal);



              //NODOS MATRIZ Propiedades y Creando Nodos de Matriz
              while(aux2 != NULL){
                  aux = aux->getDerecha();
                  while(aux!=NULL){
                      MyFile << "node" << ((Nodo_Objeto*)aux)->getXY() << "[label = \"" << ((Nodo_Objeto*)aux)->getObjeto()
                             << "\"" << ", group=" << ((Nodo_Objeto*)aux)->getY() << ", style=filled" << ", color=\""
                             << ((Nodo_Objeto*)aux)->getColor()  << "\"" << "]; \n";
                      aux = aux->getDerecha();
                  }
                  aux = aux2->getAbajo();
                  aux2 = aux2->getAbajo();
              }

              //Creando Flechas de Matriz
              MyFile << "node0" << "->" <<  "nodeY" << ((Cabecera*)tmpH)->getPos() << "; \n";
              MyFile << "node0" << "->" << "nodeX" <<((Cabecera*)tmpV)->getPos() << "; \n";

              //FLECHAS CABECERA => MATRIZ & MATRIZ = MATRIZ //Problema?
              while(tmpH != NULL){
                  if(tmpH->getDerecha() != NULL){
                      //tmpH es una cabecera, su pos = 0;
                      Nodo_Objeto* nodoAbajo = (Nodo_Objeto*)tmpH->getAbajo();
                      int posCabeceraY = ((Cabecera*)tmpH)->getPos();
                      int xAbajo = nodoAbajo->getX();
                      int primerCabeceraX = this->vertical->getPos();

                      MyFile << "nodeY" << ((Cabecera*)tmpH)->getPos() << "->" << "nodeY" << ((Cabecera*)tmpH->getDerecha())->getPos() << ";" << endl;
                      MyFile << "nodeY" << ((Cabecera*)tmpH->getDerecha())->getPos() << "->" << "nodeY" << ((Cabecera*)tmpH)->getPos() << ";" << endl;

                      if(xAbajo - primerCabeceraX > 0){
                          enlacesVaciosCabeceraArribaAbajo(MyFile, xAbajo, -1, posCabeceraY, nodoAbajo->getXY());

                      } else {
                          MyFile << "nodeY" << ((Cabecera*)tmpH)->getPos() << "->" << "node" << ((Nodo_Objeto*)tmpH->getAbajo())->getXY() << "; \n";
                          MyFile << "node" << ((Nodo_Objeto*)tmpH->getAbajo())->getXY() << "->" << "nodeY" << ((Cabecera*)tmpH)->getPos() << "; \n";
                      }

                      enlacesNodosMatrizHorizontal(MyFile, tmpH->getAbajo());
                  } else {
                      Nodo_Objeto* nodoAbajo = (Nodo_Objeto*)tmpH->getAbajo();
                      int posCabeceraY = ((Cabecera*)tmpH)->getPos();
                      int xAbajo = nodoAbajo->getX();

                      if(xAbajo - 1 > 0){
                          enlacesVaciosCabeceraArribaAbajo(MyFile, xAbajo, -1, posCabeceraY, nodoAbajo->getXY());

                      } else {
                          MyFile << "nodeY" << ((Cabecera*)tmpH)->getPos() << "->" << "node" << ((Nodo_Objeto*)tmpH->getAbajo())->getXY() << "; \n";
                          MyFile << "node" << ((Nodo_Objeto*)tmpH->getAbajo())->getXY() << "->" << "nodeY" << ((Cabecera*)tmpH)->getPos() << "; \n";
                      }

                      enlacesNodosMatrizHorizontal(MyFile, tmpH->getAbajo());
                  }
                  tmpH = tmpH->getDerecha();
              }

              //Flechaas matriz->matriz
              while(tmpV != NULL){
                  if(tmpV->getAbajo() != NULL){
                      //tmpH es una cabecera, su pos = 0;
                      Nodo_Objeto* nodoDerecha = (Nodo_Objeto*)tmpV->getDerecha();
                      int posCabeceraX = ((Cabecera*)tmpV)->getPos();
                      int yDerecha = nodoDerecha->getY();
                      int primerCabeceraY = this->horizontal->getPos();


                      MyFile << "nodeX" << ((Cabecera*)tmpV)->getPos() << "->" << "nodeX" << ((Cabecera*)tmpV->getAbajo())->getPos() << ";" << endl;
                      MyFile << "nodeX" << ((Cabecera*)tmpV->getAbajo())->getPos() << "->" << "nodeX" << ((Cabecera*)tmpV)->getPos() << ";" << endl;

                      if(yDerecha - primerCabeceraY > 0){
                          enlacesVaciosCabeceraIzquierdaDerecha(MyFile, yDerecha, -1, posCabeceraX, nodoDerecha->getXY());

                      } else {
                          MyFile << "nodeX" << ((Cabecera*)tmpV)->getPos() << "->" << "node" << ((Nodo_Objeto*)tmpV->getDerecha())->getXY() << "; \n";
                          MyFile << "node" << ((Nodo_Objeto*)tmpV->getDerecha())->getXY() << "->" << "nodeX" << ((Cabecera*)tmpV)->getPos() << "; \n";
                      }

                      enlacesNodosMatrizVertical(MyFile, tmpV->getDerecha());
                  } else {
                      Nodo_Objeto* nodoDerecha = (Nodo_Objeto*)tmpV->getDerecha();
                      int posCabeceraX = ((Cabecera*)tmpV)->getPos();
                      int yDerecha = nodoDerecha->getY();

                      if(yDerecha - 1 > 0){
                          enlacesVaciosCabeceraIzquierdaDerecha(MyFile, yDerecha, -1, posCabeceraX, nodoDerecha->getXY());
                      } else {
                          MyFile << "nodeX" << ((Cabecera*)tmpV)->getPos() << "->" << "node" << ((Nodo_Objeto*)tmpV->getDerecha())->getXY() << "; \n";
                          MyFile << "node" << ((Nodo_Objeto*)tmpV->getDerecha())->getXY() << "->" << "nodeX" << ((Cabecera*)tmpV)->getPos() << "; \n";
                      }

                      enlacesNodosMatrizVertical(MyFile, tmpV->getDerecha());
                  }
                  tmpV = tmpV->getAbajo();
              }

              //Asignando Flechas a Nodos
              tmpH = NULL;
              tmpV = NULL;


            cout << "Done";
            MyFile << "}";
            MyFile.close();
            try {
                cout << "Creating" << endl;
                system(("dot -Tps " + nombreArchivo + " -o " + nombreGrafica).c_str());


            } catch (exception e) {
                cout << "error occurred" << endl;
            }
    }
}


//Crea Nodos vacios para espacios en blanco
void Matriz::crearNodosExtraMatrizHorizontal(ofstream & MyFile, Nodo_Matriz* horizontal){
    if(horizontal == NULL){return;}
    int maxHorizontal = getLengthHorizontal();
    int maxVertical = getLengthVertical();

    for(int j= 0; j<maxHorizontal + 1; j++){
        Nodo_Matriz* actualHorizontal = this->getHorizontal(j);
        if(actualHorizontal == NULL){

        } else {
            for(int i = 0; i<maxVertical + 1; i++){
                Nodo_Matriz* actualVertical = this->getVertical(i);
                Nodo_Matriz* nodoEncontrado = getFromMatriz(i, j);
                if(actualVertical == NULL){}
                else if(nodoEncontrado!=NULL){


                }
                else {
                    MyFile << "nodeExtra" << i << j << "[label = \"" << i << "-" << j << "\"" << ", group=" << j
                           << ", style=filled" << "]; \n";
                }
            }
        }

    }
}

void Matriz::enlacesNodosMatrizHorizontal(ofstream & MyFile, Nodo_Matriz* horizontal){

    Nodo_Matriz* actual = horizontal;

    while(actual->getAbajo() != NULL){
        Nodo_Objeto* nodoObjetoActual = ((Nodo_Objeto*)actual);
        Nodo_Objeto* nodoObjetoAbajo = ((Nodo_Objeto*)actual->getAbajo());

        int xActual = nodoObjetoActual->getX();
        int xAbajo= nodoObjetoAbajo->getX();

        if((xAbajo - xActual) <= 1){
            MyFile << "node" << ((Nodo_Objeto*)actual)->getXY() << "->" << "node" <<  ((Nodo_Objeto*)actual->getAbajo())->getXY()  << "; \n";
            MyFile << "node" << ((Nodo_Objeto*)actual->getAbajo())->getXY() << "->" << "node" << ((Nodo_Objeto*)actual)->getXY() << "; \n";
        } else {
            enlacesVaciosArribaAbajo(MyFile, nodoObjetoActual->getXY(), nodoObjetoAbajo->getXY(), xActual, xAbajo, nodoObjetoActual->getY());
        }

        actual = actual->getAbajo();
    }
    if(actual->getAbajo() == NULL){
        Nodo_Objeto* nodoObjetoActual = ((Nodo_Objeto*)actual);
        int xActual = nodoObjetoActual->getX();

        Cabecera* cabeceraExistente = this->getVertical(xActual+1);
        if(cabeceraExistente){
            enlacesNodosVaciosAbajoRestantes(MyFile, nodoObjetoActual->getXY(), xActual, nodoObjetoActual->getY());
        }
    }
}

void Matriz::enlacesNodosMatrizVertical(ofstream & MyFile, Nodo_Matriz* vertical){

    Nodo_Matriz* actual = vertical;

    while(actual->getDerecha() != NULL){
        Nodo_Objeto* nodoObjetoActual = ((Nodo_Objeto*)actual);
        Nodo_Objeto* nodoObjetoDerecha = ((Nodo_Objeto*)actual->getDerecha());

        int yActual = nodoObjetoActual->getY();
        int yDerecha= nodoObjetoDerecha->getY();


        if(yDerecha - yActual <= 1){
            MyFile << "node" << ((Nodo_Objeto*)actual)->getXY() << "->" << "node" <<  ((Nodo_Objeto*)actual->getDerecha())->getXY()  << "; \n";
            MyFile << "node" << ((Nodo_Objeto*)actual->getDerecha())->getXY() << "->" << "node" << ((Nodo_Objeto*)actual)->getXY() << "; \n";
        } else {
            enlacesVaciosIzquierdaDerecha(MyFile, nodoObjetoActual->getXY(), nodoObjetoDerecha->getXY(), yActual, yDerecha, nodoObjetoActual->getX());
        }
        actual = actual->getDerecha();
    }
    if(actual->getDerecha() ==NULL){
        Nodo_Objeto* nodoObjetoActual = ((Nodo_Objeto*)actual);
        int yActual = nodoObjetoActual->getY();

        Cabecera* cabeceraExistente = this->getHorizontal(yActual+1);
        if(cabeceraExistente){
            enlacesNodosVaciosDerechaRestantes(MyFile, nodoObjetoActual->getXY(), yActual, nodoObjetoActual->getX());
        }

    }
}

//Metodos para nodos vacios
void Matriz::agregarNodosVaciosARank(ofstream & MyFile, int x){
    if(horizontal == NULL){return;}
    int maxHorizontal = getLengthHorizontal();

        Cabecera* actualVertical = this->getVertical(x);
        if(actualVertical == NULL){

        } else {
            for(int i = 0; i<maxHorizontal + 1; i++){
                Nodo_Matriz* actualHorizontal = this->getHorizontal(i);
                Nodo_Matriz* nodoEncontrado = getFromMatriz(x, i);
                Nodo_Matriz* nodoEncontradoNext = getFromMatriz(x, i+1);
                if(actualHorizontal == NULL){}
                else if(nodoEncontrado!=NULL){
                }
                else {
                    if(i == maxHorizontal){
                        MyFile << ", "  << "nodeExtra" << x << i;
                    } else {
                        MyFile << ", " << "nodeExtra" << x << i;
                    }
                }
            }
        }

}

void Matriz::enlacesVaciosArribaAbajo(ofstream & MyFile, string idActual, string idAbajo, int xActual, int xAbajo, int y){ //PRoblema no hago validacion si la cabecera existe en atual-1
    MyFile << "node" << idActual << "->" << "nodeExtra" << xActual+1 << y << "; \n";
    MyFile << "nodeExtra" << xActual +1 << y << "->" << "node" << idActual << "; \n";

    MyFile << "nodeExtra" << xAbajo -1 << y << "->" << "node" << idAbajo << "; \n";
    MyFile << "node" << idAbajo << "->" << "nodeExtra" << xAbajo-1 << y << "; \n";

    for(int i = xActual + 1; i < xAbajo - 1; i++){
        MyFile << "nodeExtra" << i << y << "->" << "nodeExtra" << i+1 << y << "; \n";
        MyFile << "nodeExtra" << i+1 << y << "->" << "nodeExtra" << i << y << "; \n";
    }

}

void Matriz::enlacesNodosVaciosAbajoRestantes(ofstream & MyFile, string idActual, int xActual, int y){
    int cantidadX = this->getLengthVertical();

    if(cantidadX == xActual){    }
    else {
        MyFile << "node" << idActual << "->" << "nodeExtra" << xActual+1 << y << "; \n";
        MyFile << "nodeExtra" << xActual +1 << y << "->" << "node" << idActual << "; \n";

        for(int i = xActual + 1; i < cantidadX-1; i++){
            MyFile << "nodeExtra" << i << y << "->" << "nodeExtra" << i+1 << y << "; \n";
            MyFile << "nodeExtra" << i+1 << y << "->" << "nodeExtra" << i << y << "; \n";
        }

    }

}

void Matriz::enlacesVaciosIzquierdaDerecha(ofstream & MyFile, string idActual, string idDerecha, int yActual, int yDerecha, int x){ //PRoblema no hago validacion si la cabecera existe en atual-1
    MyFile << "node" << idActual << "->" << "nodeExtra" << x << yActual+1 << "; \n";
    MyFile << "nodeExtra" << x << yActual +1 << "->" << "node" << idActual << "; \n";

    MyFile << "nodeExtra" << x << yDerecha -1 << "->" << "node" << idDerecha << "; \n";
    MyFile << "node" << idDerecha << "->" << "nodeExtra" << x << yDerecha -1 << "; \n";

    for(int i = yActual + 1; i < yDerecha - 1; i++){
        MyFile << "nodeExtra" << x << i << "->" << "nodeExtra" << x << i+1 << "; \n";
        MyFile << "nodeExtra" << x << i+1 << "->" << "nodeExtra" << x << i << "; \n";
    }

}

void Matriz::enlacesNodosVaciosDerechaRestantes(ofstream & MyFile, string idActual, int yActual, int x){
    int cantidadY = this->getLengthHorizontal();

    if(cantidadY == yActual){    }
    else {
        MyFile << "node" << idActual << "->" << "nodeExtra" << x << yActual+1 << "; \n";
        MyFile << "nodeExtra" << x << yActual +1 << "->" << "node" << idActual << "; \n";

        for(int i = yActual + 1; i < cantidadY-1; i++){
            MyFile << "nodeExtra" << x << i << "->" << "nodeExtra" << x << i+1 << "; \n";
            MyFile << "nodeExtra" << x << i+1 << "->" << "nodeExtra" << x << i << "; \n";
        }

    }

}

void Matriz::enlacesVaciosCabeceraArribaAbajo(ofstream &MyFile, int xAbajo, int xCabecera, int posCabeceraY, string idAbajo){

    int diferencia = xAbajo - xCabecera;
    int cantidadNodos = diferencia - 1;

    if(xAbajo-1 == xCabecera){    }
    else {

        for(int i = xCabecera+1; i < xAbajo; i++){
            Cabecera* cabeceraExistenteSiguiente = getVertical(i);

            if(cabeceraExistenteSiguiente){
                MyFile << "nodeY" << posCabeceraY << "->" << "nodeExtra" << i << posCabeceraY << "; \n";
                MyFile << "nodeExtra" << i << posCabeceraY << "->" << "nodeY" << posCabeceraY << "; \n";
                break;
            }
        }
        for(int i = xAbajo-1; i > xCabecera; i--){
            Cabecera* cabeceraExistenteSiguiente = getVertical(i);

            if(cabeceraExistenteSiguiente){
                MyFile << "node" << idAbajo << "->" << "nodeExtra" << i << posCabeceraY << "; \n";
                MyFile << "nodeExtra" << i << posCabeceraY << "->" << "node" << idAbajo << "; \n";
                break;
            }
        }
        for(int i = xCabecera + 1; i < cantidadNodos-1; i++){
            Cabecera* cabeceraExistente = getVertical(i);
            Cabecera* cabeceraExistenteSiguiente = getVertical(i+1);
            if(cabeceraExistente){
                MyFile << "nodeExtra" << i << posCabeceraY << "->" << "nodeExtra" << i+1 << posCabeceraY << "; \n";
                MyFile << "nodeExtra" << i+1 << posCabeceraY << "->" << "nodeExtra" << i << posCabeceraY << "; \n";
            }
        }

    }

}

void Matriz::enlacesVaciosCabeceraIzquierdaDerecha(ofstream &MyFile, int yDerecha, int yCabecera, int posCabeceraX, string idDerecha){

    int diferencia = yDerecha - yCabecera;
    int cantidadNodos = diferencia - 1;

    if(yDerecha-1 == yCabecera){    }
    else {

        for(int i = yCabecera+1; i < yDerecha; i++){
            Cabecera* cabeceraExistenteSiguiente = getHorizontal(i);

            if(cabeceraExistenteSiguiente){
                MyFile << "nodeX" << posCabeceraX << "->" << "nodeExtra"<< posCabeceraX << i  << "; \n";
                MyFile << "nodeExtra" << posCabeceraX << i << "->" << "nodeX" << posCabeceraX << "; \n";
                break;
            }
        }
        for(int i = yDerecha-1; i > yCabecera; i--){
            Cabecera* cabeceraExistenteSiguiente = getHorizontal(i);

            if(cabeceraExistenteSiguiente){
                MyFile << "node" << idDerecha << "->" << "nodeExtra" << posCabeceraX << i  << "; \n";
                MyFile << "nodeExtra" << posCabeceraX << i  << "->" << "node" << idDerecha << "; \n";
                break;
            }
        }
        for(int i = yCabecera + 1; i < cantidadNodos-1; i++){
            Cabecera* cabeceraExistente = getHorizontal(i);
            Cabecera* cabeceraExistenteSiguiente = getHorizontal(i+1);
            if(cabeceraExistente){
                MyFile << "nodeExtra" << posCabeceraX << i  << "->" << "nodeExtra" << posCabeceraX << i+1 << "; \n";
                MyFile << "nodeExtra" << posCabeceraX << i+1  << "->" << "nodeExtra" << posCabeceraX << i  << "; \n";
            }
        }

    }

}

//Metodos para ayudar a nodos Vacios

int Matriz::getLengthHorizontal(){
    Nodo_Matriz* actual = (Nodo_Matriz*)this->horizontal;
    int distancia = 0;

    if(actual == NULL){
        return 0;
    }
    else{
        while(actual != NULL){
            distancia++;
            actual = actual->getDerecha();
        }
    }

    return distancia;

}

int Matriz::getLengthVertical(){
    Nodo_Matriz* actual = (Nodo_Matriz*)this->vertical;
    int distancia = 0;

    if(actual == NULL){
        return 0;
    }
    else{
        while(actual != NULL){
            distancia++;
            actual = actual->getAbajo();
        }
    }

    return distancia;

}

Nodo_Matriz* Matriz::getFromMatriz(int x, int y){
    Nodo_Matriz* aux = this->vertical;
    Nodo_Matriz* aux2 = this->vertical->getAbajo();


    while(aux != NULL){
        aux=aux->getDerecha();
        while(aux != NULL){
            int yActual = (((Nodo_Objeto*)aux)->getY());
            int xActual = (((Nodo_Objeto*)aux)->getX());
            if(y == yActual && x == xActual){
                   return aux;
            }
            if(yActual > y && xActual > x){
                return NULL;
            }
            aux = aux->getDerecha();
        }
        aux = aux2;
        if(aux2 != NULL){
            aux2 = aux2->getAbajo();
        }
    }
    return NULL;

}

//Enlaza Verticalmente nodos vacios
void Matriz::enlacesNodosVaciosVertical(ofstream &MyFile){
        Nodo_Matriz* actual = this->horizontal->getAbajo();
        Nodo_Matriz* actual2 = actual->getAbajo();
        while(actual != NULL){
            while(actual->getDerecha() != NULL){
                int yActual = ((Nodo_Objeto*)actual)->getY();
                int yDerecha= ((Nodo_Objeto*)actual->getDerecha())->getY();
                int fila = ((Nodo_Objeto*)actual)->getX();

                if((yDerecha - yActual) > 1){
                    MyFile << "node" << ((Nodo_Objeto*)actual)->getXY() << "->" << "nodeExtra" << fila << yActual+1 << "; \n";
                    MyFile << "nodeExtra" << fila << yActual +1 << "->" << "node" << ((Nodo_Objeto*)actual)->getXY() << "; \n";

                    MyFile << "nodeExtra" << fila << yDerecha -1 << "->" << "node" << ((Nodo_Objeto*)actual->getDerecha())->getXY() << "; \n";
                    MyFile << "node" << ((Nodo_Objeto*)actual->getDerecha())->getXY() << "->" << "nodeExtra" << fila << yDerecha-1 << "; \n";

                    for(int i = yActual + 1; i < yDerecha - 1; i++){
                        MyFile << "nodeExtra" << fila << i << "->" << "nodeExtra" << fila << i+1 << "; \n";
                        MyFile << "nodeExtra" << fila << i+1 << "->" << "nodeExtra" << fila << i << "; \n";
                    }
                }
                actual=actual->getDerecha();

            }
            if(actual->getDerecha() == NULL){
                int yActual = ((Nodo_Objeto*)actual)->getY();
                int yMaxima = this->getLengthHorizontal();
                int fila = ((Nodo_Objeto*)actual)->getX();

                if(yActual == yMaxima){}
                else {
                    MyFile << "node" << ((Nodo_Objeto*)actual)->getXY() << "->" << "nodeExtra" << fila << yActual+1 << "; \n";
                    MyFile << "nodeExtra" << fila << yActual +1 << "->" << "node" << ((Nodo_Objeto*)actual)->getXY() << "; \n";

                    for(int i = yActual + 1; i < yMaxima; i++){
                        MyFile << "nodeExtra" << fila << i << "->" << "nodeExtra" << fila << i+1 << "; \n";
                        MyFile << "nodeExtra" << fila << i+1 << "->" << "nodeExtra" << fila << i << "; \n";
                    }
                }
            }
            actual = actual2;
            if(actual2!=NULL){
                actual2= actual2->getAbajo();
            }
        }

}

//Metodos para Reportes

int Matriz::getVentanas(){
    Nodo_Matriz* aux = this->vertical;
    Nodo_Matriz* aux2 = this->vertical->getAbajo();
    int ventanas = 0;


    while(aux != NULL){
        aux=aux->getDerecha();
        while(aux != NULL){

            if((((Nodo_Objeto*)aux)->getObjeto() == "ventana") || (((Nodo_Objeto*)aux)->getObjeto() == "Ventana")){
                   ventanas++;
            }
            aux = aux->getDerecha();
        }
        aux = aux2;
        if(aux2 != NULL){
            aux2 = aux2->getAbajo();
        }
    }
    return ventanas;
}

int Matriz::getEspacio(){
    int maxHorizontal = getLengthHorizontal();
    int maxVertical = getLengthVertical();
    int espacioLibre = 0;

    for(int j= 0; j<maxHorizontal + 1; j++){
        Nodo_Matriz* actualHorizontal = this->getHorizontal(j);
        if(actualHorizontal == NULL){

        } else {
            for(int i = 0; i<maxVertical + 1; i++){
                Nodo_Matriz* actualVertical = this->getVertical(i);
                Nodo_Matriz* nodoEncontrado = getFromMatriz(i, j);
                if(actualVertical == NULL){}
                else if(nodoEncontrado!=NULL){

//aqui
                }
                else {
                    espacioLibre++;
                }
            }
        }

    }
    return espacioLibre;
}

int Matriz::getParedes(){
    Nodo_Matriz* aux = this->vertical;
    Nodo_Matriz* aux2 = this->vertical->getAbajo();
    int paredes = 0;


    while(aux != NULL){
        aux=aux->getDerecha();
        while(aux != NULL){

            if((((Nodo_Objeto*)aux)->getObjeto() == "pared") || (((Nodo_Objeto*)aux)->getObjeto() == "Pared")){
                   paredes++;
            }
            aux = aux->getDerecha();
        }
        aux = aux2;
        if(aux2 != NULL){
            aux2 = aux2->getAbajo();
        }
    }
    return paredes;
}

int Matriz::getObjetos(){
//    Nodo_Matriz* aux = this->vertical;
//    Nodo_Matriz* aux2 = this->vertical->getAbajo();
//    int objetos = 0;


//    while(aux != NULL){
//        aux=aux->getDerecha();
//        while(aux != NULL){
//            string objetoActual = ((Nodo_Objeto*)aux)->getObjeto();

//            if(objetoActual != "ventana" && objetoActual != "Ventana" &&
//                   objetoActual != "pared" && objetoActual != "Pared"
//                    && objetoActual != ""){
//                   objetos++;
//            }
//            aux = aux->getDerecha();
//        }
//        aux = aux2;
//        if(aux2 != NULL){
//            aux2 = aux2->getAbajo();
//        }
//    }

    return this->objetos;
}

void Matriz::sumarCantidadObjeto(){
    this->objetos = this->objetos+1;
}

//Copiar Nivel

Matriz* Matriz::copiarMatriz(){
    Nodo_Matriz* aux = this->vertical;
    Nodo_Matriz* aux2 = this->vertical->getAbajo();
    Matriz* matrizCopiada = new Matriz();


    while(aux != NULL){
        aux=aux->getDerecha();
        while(aux != NULL){
            int yActual = (((Nodo_Objeto*)aux)->getY());
            int xActual = (((Nodo_Objeto*)aux)->getX());
            int id = (((Nodo_Objeto*)aux)->getId());
            string objeto = (((Nodo_Objeto*)aux)->getObjeto());
            string color = (((Nodo_Objeto*)aux)->getColor());
            char letra = (((Nodo_Objeto*)aux)->getLetra());

            Nodo_Objeto* nodoPorAgregar = new Nodo_Objeto(id, objeto, letra, color, xActual, yActual);
            matrizCopiada->add(nodoPorAgregar);


            aux = aux->getDerecha();
        }
        aux = aux2;
        if(aux2 != NULL){
            aux2 = aux2->getAbajo();
        }
    }
    return matrizCopiada;
}

void Matriz::eliminarParedes(int x1, int y1, int x2, int y2){
    if(x1 == x2 && y1 ==y2){
        Nodo_Matriz* NodoABorrar = getFromMatriz(x1, y1);

        string objeto = "Nada";

        if(NodoABorrar != NULL){
            objeto = ((Nodo_Objeto*)NodoABorrar)->getObjeto();
        }

        if(NodoABorrar != NULL && ( objeto == "pared" || objeto == "Pared")){
            if(NodoABorrar->getDerecha() != NULL){
                NodoABorrar->getDerecha()->setIzquierda(NodoABorrar->getIzquierda());
            }
            if(NodoABorrar->getIzquierda() != NULL){
                NodoABorrar->getIzquierda()->setDerecha(NodoABorrar->getDerecha());

            }
            if(NodoABorrar->getAbajo() != NULL){
                NodoABorrar->getAbajo()->setArriba(NodoABorrar->getArriba());
            }
            if(NodoABorrar->getArriba() != NULL){
                NodoABorrar->getArriba()->setAbajo(NodoABorrar->getAbajo());
            }

            delete NodoABorrar;

            Cabecera* cabeceraX = getVertical(x1);
            Cabecera* cabeceraY = getHorizontal(y1);

            Nodo_Matriz* ultimoVertical = obtenerUltimoVertical(cabeceraY, x1);
            Nodo_Matriz* ultimoHorizontal = obtenerUltimoHorizontal(cabeceraX, y1);

            if(ultimoHorizontal == cabeceraX){
                if(cabeceraX->getAbajo() != NULL){
                    cabeceraX->getAbajo()->setArriba(cabeceraX->getArriba());
                }
                if(cabeceraX->getArriba() != NULL){
                    cabeceraX->getArriba()->setAbajo(cabeceraX->getAbajo());
                }
                delete cabeceraX;
            }
            if(ultimoVertical == cabeceraY){
                if(cabeceraY->getDerecha() != NULL){
                    cabeceraY->getDerecha()->setIzquierda(cabeceraY->getIzquierda());
                }
                if(cabeceraY->getIzquierda() != NULL){
                    cabeceraY->getIzquierda()->setDerecha(cabeceraY->getDerecha());
                }
                delete cabeceraY;
            }
        }

    }
    else if(x1 == x2){
        for(int j = y1; j < y2+1; j++){
            Nodo_Matriz* NodoABorrar = getFromMatriz(x1, j);
            string objeto = "Nada";

            if(NodoABorrar != NULL){
                objeto = ((Nodo_Objeto*)NodoABorrar)->getObjeto();
            }

            if(NodoABorrar != NULL && ( objeto == "pared" || objeto == "Pared")){
                if(NodoABorrar->getDerecha() != NULL){
                    NodoABorrar->getDerecha()->setIzquierda(NodoABorrar->getIzquierda());
                }
                if(NodoABorrar->getIzquierda() != NULL){
                    NodoABorrar->getIzquierda()->setDerecha(NodoABorrar->getDerecha());

                }
                if(NodoABorrar->getAbajo() != NULL){
                    NodoABorrar->getAbajo()->setArriba(NodoABorrar->getArriba());
                }
                if(NodoABorrar->getArriba() != NULL){
                    NodoABorrar->getArriba()->setAbajo(NodoABorrar->getAbajo());
                }

                delete NodoABorrar;

                Cabecera* cabeceraX = getVertical(x1);
                Cabecera* cabeceraY = getHorizontal(j);

                Nodo_Matriz* ultimoVertical = obtenerUltimoVertical(cabeceraY, x1);
                Nodo_Matriz* ultimoHorizontal = obtenerUltimoHorizontal(cabeceraX, y1);

                if(ultimoHorizontal == cabeceraX){
                    if(cabeceraX->getAbajo() != NULL){
                        cabeceraX->getAbajo()->setArriba(cabeceraX->getArriba());
                    }
                    if(cabeceraX->getArriba() != NULL){
                        cabeceraX->getArriba()->setAbajo(cabeceraX->getAbajo());
                    }
                    delete cabeceraX;
                }
                if(ultimoVertical == cabeceraY){
                    if(cabeceraY->getDerecha() != NULL){
                        cabeceraY->getDerecha()->setIzquierda(cabeceraY->getIzquierda());
                    }
                    if(cabeceraY->getIzquierda() != NULL){
                        cabeceraY->getIzquierda()->setDerecha(cabeceraY->getDerecha());
                    }
                    delete cabeceraY;
                }
            }
        }
    }
    else if(y1 == y2){
        for(int i = x1; i < x2+1; i++){
            Nodo_Matriz* NodoABorrar = getFromMatriz(i, y1);
            string objeto = "Nada";

            if(NodoABorrar != NULL){
                objeto = ((Nodo_Objeto*)NodoABorrar)->getObjeto();
            }

            if(NodoABorrar != NULL && ( objeto == "pared" || objeto == "Pared")){
                if(NodoABorrar->getDerecha() != NULL){
                    NodoABorrar->getDerecha()->setIzquierda(NodoABorrar->getIzquierda());
                }
                if(NodoABorrar->getIzquierda() != NULL){
                    NodoABorrar->getIzquierda()->setDerecha(NodoABorrar->getDerecha());

                }
                if(NodoABorrar->getAbajo() != NULL){
                    NodoABorrar->getAbajo()->setArriba(NodoABorrar->getArriba());
                }
                if(NodoABorrar->getArriba() != NULL){
                    NodoABorrar->getArriba()->setAbajo(NodoABorrar->getAbajo());
                }
                NodoABorrar = NULL;

                Cabecera* cabeceraX = getVertical(x1);
                Cabecera* cabeceraY = getHorizontal(y1);

                Nodo_Matriz* ultimoVertical = obtenerUltimoVertical(cabeceraY, x1);
                Nodo_Matriz* ultimoHorizontal = obtenerUltimoHorizontal(cabeceraX, y1);

                if(ultimoVertical == cabeceraY){
                    cabeceraY->getDerecha()->setIzquierda(cabeceraY->getIzquierda());
                    if(cabeceraY->getIzquierda() != NULL){
                        cabeceraY->getIzquierda()->setDerecha(cabeceraY->getDerecha());
                    }
                    delete cabeceraY;
                }
                if(ultimoHorizontal == cabeceraX){
                    cabeceraX->getAbajo()->setArriba(cabeceraX->getArriba());
                    if(cabeceraX->getArriba() != NULL){
                        cabeceraX->getArriba()->setAbajo(cabeceraX->getAbajo());
                    }
                    delete cabeceraX;
                }
            }
        }
    }
}

void Matriz::eliminarObjeto(int id, int longitudObjeto){
    int vez = 0;
    int cantidadObjetos = 0;

    for(int j = 0; j < this->getLengthHorizontal()+1; j++){
        for(int i = 0; i < this->getLengthVertical()+1; i++){
            Nodo_Matriz* NodoABorrar = getFromMatriz(i, j);
            int idObjeto = 0;

            if(NodoABorrar != NULL){
                idObjeto = ((Nodo_Objeto*)NodoABorrar)->getId();
            }

            if(NodoABorrar != NULL && ( idObjeto == id)){
                if(NodoABorrar->getDerecha() != NULL){
                    NodoABorrar->getDerecha()->setIzquierda(NodoABorrar->getIzquierda());
                }
                if(NodoABorrar->getIzquierda() != NULL){
                    NodoABorrar->getIzquierda()->setDerecha(NodoABorrar->getDerecha());

                }
                if(NodoABorrar->getAbajo() != NULL){
                    NodoABorrar->getAbajo()->setArriba(NodoABorrar->getArriba());
                }
                if(NodoABorrar->getArriba() != NULL){
                    NodoABorrar->getArriba()->setAbajo(NodoABorrar->getAbajo());
                }

                delete NodoABorrar;

                Cabecera* cabeceraX = getVertical(i);
                Cabecera* cabeceraY = getHorizontal(j);

                Nodo_Matriz* ultimoVertical = obtenerUltimoVertical(cabeceraY, i);
                Nodo_Matriz* ultimoHorizontal = obtenerUltimoHorizontal(cabeceraX, j);

                if(ultimoHorizontal == cabeceraX){
                    if(cabeceraX->getAbajo() != NULL){
                        cabeceraX->getAbajo()->setArriba(cabeceraX->getArriba());
                    }
                    if(cabeceraX->getArriba() != NULL){
                        cabeceraX->getArriba()->setAbajo(cabeceraX->getAbajo());
                    }
                    delete cabeceraX;
                }
                if(ultimoVertical == cabeceraY){
                    if(cabeceraY->getDerecha() != NULL){
                        cabeceraY->getDerecha()->setIzquierda(cabeceraY->getIzquierda());
                    }
                    if(cabeceraY->getIzquierda() != NULL){
                        cabeceraY->getIzquierda()->setDerecha(cabeceraY->getDerecha());
                    }
                    delete cabeceraY;
                }
                //Para Eliminar Objetos
                vez++;
                if(vez == longitudObjeto){
                    vez = 0;
                    cantidadObjetos++;
                }
            }
        }
    }
    this->objetos = objetos - cantidadObjetos;
}
