#include "menueditarnivel2.h"

menuEditarNivel2::menuEditarNivel2(NodoArbol* proyecto, Arbol_Binario* arbolObjetos, int idProyecto)
{
    this->proyecto = proyecto;
    this->arbolObjetos = arbolObjetos;
    this->idProyecto = idProyecto;
}


void menuEditarNivel2::mostrarNiveles(){

    imprimirEspacios(5);
    Lista_Niveles* listaNIvelesActual = this->proyecto->getListaNiveles();

    listaNIvelesActual->imprimirNiveles();

    imprimirEspacios(5);

    int idNivel;

    cout << "Ingrese Nivel a Editar: ";
    cin >> idNivel;
    graficarNivel(idNivel);

    Nodo_Nivel* nivelActual = this->proyecto->getListaNiveles()->getNodo(idNivel);

    imprimirEspacios(10);

    string opciones[] = {"3.1. Agregar Objeto", "3.2. Eliminar Objeto", "3.3. Eliminar Pared",
                         "3.4. Copiar Nivel", "3.5. Crear cantidad pisos", "3.6. Mover Objeto", "3.7 Salir"};

    bool isContinue = true;
    int opcion = 0;

    while(isContinue != false){
        imprimirEspacios(5);
        for(int i = 0; i < 7 ; i++){
            cout << opciones[i] << endl;
        }

        cout << "Escoja su opcion: ";

        cin >> opcion;

        if(opcion == 1){

            agregarObjeto(nivelActual);

            imprimirEspacios(10);
        }
        if(opcion == 2){
            eliminarObjeto(nivelActual);
            imprimirEspacios(10);
        }
        if(opcion == 3){

            eliminarPared(nivelActual);
            imprimirEspacios(10);
        }
        if(opcion == 4){
            copiarNivel();
            graficarNivel(idNivel);
            imprimirEspacios(10);

        }
        if(opcion == 5){
        }
        if(opcion == 6){
        }
        if(opcion == 7){
            isContinue = false;
        }
        graficarNivel(idNivel);
    }

}


void menuEditarNivel2::graficarNivel(int id){
    string nombre = "Proyecto_" + this->proyecto->getName() + "_Nivel" + to_string(id);
    Matriz* matrizActual = this->proyecto->getListaNiveles()->getNodo(id)->getMatriz();
    matrizActual->crearGrafica(nombre);
}

void menuEditarNivel2::agregarObjeto(Nodo_Nivel* nivelActual){

    this->arbolObjetos->recorrerInorden(this->arbolObjetos->getRaiz());

    int x, y, id, grados, xInicialObjeto, yInicialObjeto, idObjeto;
    string objeto, color;
    char letra;

    cout << "Seleccione Objeto a agregar: ";
    cin >> id;
    Nodo_Binario* nodoAgregar = this->arbolObjetos->getObjeto(id, this->arbolObjetos->getRaiz());

    cout << "Inserte posicion X: ";
    cin >> x;
    imprimirEspacios(1);
    cout << "Inserte posicion Y: ";
    cin >> y;
    imprimirEspacios(1);
    cout << "Inserte grados (0/45/90/180/270): ";
    cin >> grados;
    imprimirEspacios(1);



    int size = nodoAgregar->getListaPuntos()->getSizeNodos();
    Lista_Puntos* listaActualPuntos = nodoAgregar->getListaPuntos();
    xInicialObjeto = listaActualPuntos->gethead()->getX();
    yInicialObjeto = listaActualPuntos->gethead()->getY();
    objeto = nodoAgregar->getName();
    color = nodoAgregar->getColor();
    letra = nodoAgregar->getLetra();
    int posX = 0;
    int posY = 0;
    int posNuevaX45;
    int posNuevaY45;

    //Agregamos al ABB del nivel (Jalamos del universal)
    nivelActual->getABB()->insertar(id, objeto, letra, color, listaActualPuntos);
    nivelActual->getABB()->crearGrafica(this->proyecto->getName(), nivelActual->getId());


    if(grados == 0){
        //Agregar Nodos en X
        for(int i = 0; i < size; i++){
            if(xInicialObjeto-listaActualPuntos->getPunto(i)->getX() <= xInicialObjeto){
                posX = x + (xInicialObjeto-listaActualPuntos->getPunto(i)->getX())*-1;
            } else{
                posX = x - xInicialObjeto-listaActualPuntos->getPunto(i)->getX();
            }

            if(yInicialObjeto-listaActualPuntos->getPunto(i)->getY() <= yInicialObjeto){
                posY = y + (yInicialObjeto-listaActualPuntos->getPunto(i)->getY())*-1;
            } else{
                posY = y - yInicialObjeto-listaActualPuntos->getPunto(i)->getY();
            }
            Nodo_Objeto* nodoAgregado = new Nodo_Objeto(id, objeto, letra, color, posX, posY);

            nivelActual->getMatriz()->add(nodoAgregado);

        }

    } else if (grados == 45){
        for(int i = 0; i < size; i++){
            //Ponemos las x en donde son sin rotaciones
            if(xInicialObjeto-listaActualPuntos->getPunto(i)->getX() <= xInicialObjeto){
                posX = x + (xInicialObjeto-listaActualPuntos->getPunto(i)->getX())*-1;
            } else{
                posX = x - xInicialObjeto-listaActualPuntos->getPunto(i)->getX();
            }

            if(yInicialObjeto-listaActualPuntos->getPunto(i)->getY() <= yInicialObjeto){
                posY = y + (yInicialObjeto-listaActualPuntos->getPunto(i)->getY())*-1;
            } else{
                posY = y - yInicialObjeto-listaActualPuntos->getPunto(i)->getY();
            }

            //Comenzamos a rotar
            if(i != 0){
                int diferenciaX = listaActualPuntos->getPunto(i)->getX() - xInicialObjeto;
                int diferenciaY = listaActualPuntos->getPunto(i)->getY() - yInicialObjeto;
                Nodo_Puntos* nodoPuntosActual = listaActualPuntos->getPunto(i);
                Nodo_Puntos* nodoSiguiente = listaActualPuntos->getPunto(i+1);
                Nodo_Puntos* nodoAnterior = listaActualPuntos->getPunto(i-1);

                //Rotaciones cuando esta inclinado 45 grados
                if(abs(diferenciaX) == abs(diferenciaY)){
                    if(nodoAnterior!= NULL && nodoAnterior->getX() != nodoPuntosActual->getX()
                            && nodoAnterior->getY() == nodoPuntosActual->getY()){
                        if(diferenciaX < 0){
                            posNuevaX45 = x - abs(diferenciaX) + 1;
                            posNuevaY45 = y + abs(diferenciaX) + 1;
                        }if(diferenciaX > 0){
                            posNuevaX45 = x + abs(diferenciaX) + 1;
                            posNuevaY45 = y + abs(diferenciaX) - 1;
                        }
                    }
                    else if(diferenciaY > 0){ //El Nodo Actual esta a la derecha del inicio
                        if(diferenciaX > 0){ //Nodo Actual esta abajo (mayor)
                            posNuevaY45 = y;
                            posNuevaX45 = x + diferenciaX;
                        }
                        if(diferenciaX < 0){ //Nodo Actual esta arriba (menor)
                            posNuevaX45 = x;
                            posNuevaY45 = y + abs(diferenciaY);
                        }

                    }
                    else if(diferenciaY < 0){ //El Nodo Actual esta a la izquierda del inicio
                        if(diferenciaX > 0){ //Nodo Actual esta abajo (Mayor)
                            posNuevaY45 = y - abs(diferenciaY);
                            posNuevaX45 = x;
                        }
                        if(diferenciaX < 0){ //Nodo Actual esta arriba(menor)
                            posNuevaX45 = x - abs(diferenciaX);
                            posNuevaY45 = y;
                        }
                    }

                }
                //Rotaciones cuando esta en algun plano x o y
                else if(diferenciaX == 0){
                    if(diferenciaY > 0){
                        posNuevaY45 = y + abs(diferenciaY);
                        posNuevaX45 = x + abs(diferenciaY);
                    }
                    if(diferenciaY < 0){
                        posNuevaX45 = x - abs(diferenciaY);
                        posNuevaY45 = y - abs(diferenciaY);
                    }
                }
                else if(diferenciaY == 0){
                    if(diferenciaX > 0){
                        posNuevaY45 = y - abs(diferenciaX);
                        posNuevaX45 = x + abs(diferenciaX);
                    }
                    if(diferenciaX < 0){
                        posNuevaX45 = x - abs(diferenciaX);
                        posNuevaY45 = y + abs(diferenciaX);
                    }
                }


            } else {
                posNuevaX45 = posX;
                posNuevaY45 = posY;
            }

            Nodo_Objeto* nodoAgregado = new Nodo_Objeto(id, objeto, letra, color, posNuevaX45, posNuevaY45);

            nivelActual->getMatriz()->add(nodoAgregado);
        }
    }
    else if (grados == 90){
        for(int i = 0; i < size; i++){
            //Ponemos las x en donde son sin rotaciones
            if(xInicialObjeto-listaActualPuntos->getPunto(i)->getX() <= xInicialObjeto){
                posX = x + (xInicialObjeto-listaActualPuntos->getPunto(i)->getX())*-1;
            } else{
                posX = x - xInicialObjeto-listaActualPuntos->getPunto(i)->getX();
            }

            if(yInicialObjeto-listaActualPuntos->getPunto(i)->getY() <= yInicialObjeto){
                posY = y + (yInicialObjeto-listaActualPuntos->getPunto(i)->getY())*-1;
            } else{
                posY = y - yInicialObjeto-listaActualPuntos->getPunto(i)->getY();
            }

            //Comenzamos a rotar
            if(i != 0){
                int diferenciaX = listaActualPuntos->getPunto(i)->getX() - xInicialObjeto;
                int diferenciaY = listaActualPuntos->getPunto(i)->getY() - yInicialObjeto;
                Nodo_Puntos* nodoPuntosActual = listaActualPuntos->getPunto(i);
                Nodo_Puntos* nodoSiguiente = listaActualPuntos->getPunto(i+1);
                Nodo_Puntos* nodoAnterior = listaActualPuntos->getPunto(i-1);

                //Rotaciones cuando esta inclinado 45 grados
                if(abs(diferenciaX) == abs(diferenciaY)){
                    if(nodoAnterior!= NULL && nodoAnterior->getX() != nodoPuntosActual->getX()
                            && nodoAnterior->getY() == nodoPuntosActual->getY()){
                        if(diferenciaX < 0){
                            posNuevaX45 = x - abs(diferenciaX) + 1;
                            posNuevaY45 = y + abs(diferenciaX) + 1;
                        }if(diferenciaX > 0){
                            posNuevaX45 = x + abs(diferenciaX) + 1;
                            posNuevaY45 = y + abs(diferenciaX) - 1;
                        }
                    }
                    else if(diferenciaY > 0){ //El Nodo Actual esta a la derecha del inicio
                        if(diferenciaX > 0){ //Nodo Actual esta abajo (mayor)
                            posNuevaY45 = y;
                            posNuevaX45 = x + diferenciaX;
                        }
                        if(diferenciaX < 0){ //Nodo Actual esta arriba (menor)
                            posNuevaX45 = x;
                            posNuevaY45 = y + abs(diferenciaY);
                        }

                    }
                    else if(diferenciaY < 0){ //El Nodo Actual esta a la izquierda del inicio
                        if(diferenciaX > 0){ //Nodo Actual esta abajo (Mayor)
                            posNuevaY45 = y - abs(diferenciaY);
                            posNuevaX45 = x;
                        }
                        if(diferenciaX < 0){ //Nodo Actual esta arriba(menor)
                            posNuevaX45 = x - abs(diferenciaX);
                            posNuevaY45 = y;
                        }
                    }

                }
                //Rotaciones cuando esta en algun plano x o y
                else if(diferenciaX == 0){
                    if(diferenciaY > 0){
                        posNuevaY45 = y + abs(diferenciaY);
                        posNuevaX45 = x + abs(diferenciaY);
                    }
                    if(diferenciaY < 0){
                        posNuevaX45 = x - abs(diferenciaY);
                        posNuevaY45 = y - abs(diferenciaY);
                    }
                }
                else if(diferenciaY == 0){
                    if(diferenciaX > 0){
                        posNuevaY45 = y - abs(diferenciaX);
                        posNuevaX45 = x + abs(diferenciaX);
                    }
                    if(diferenciaX < 0){
                        posNuevaX45 = x - abs(diferenciaX);
                        posNuevaY45 = y + abs(diferenciaX);
                    }
                }


            } else {
                posNuevaX45 = posX;
                posNuevaY45 = posY;
            }

            Nodo_Objeto* nodoAgregado = new Nodo_Objeto(id, objeto, letra, color, posNuevaX45, posNuevaY45);

            nivelActual->getMatriz()->add(nodoAgregado);
        }
    }
    else if (grados == 180){
    }
    else if (grados == 270){

    }

    this->proyecto->getListaNiveles()->aumentarObjetos(1);

}

Nodo_Objeto* menuEditarNivel2::metodoGiro(Nodo_Binario* nodoAgregar, int x, int y, int grados){

    int xInicialObjeto, yInicialObjeto;
    string objeto, color;
    char letra;

    int size = nodoAgregar->getListaPuntos()->getSizeNodos();
    Lista_Puntos* listaActualPuntos = nodoAgregar->getListaPuntos();
    xInicialObjeto = listaActualPuntos->gethead()->getX();
    yInicialObjeto = listaActualPuntos->gethead()->getY();
    objeto = nodoAgregar->getName();
    color = nodoAgregar->getColor();
    letra = nodoAgregar->getLetra();
    int id = nodoAgregar->getId();
    int posX = 0;
    int posY = 0;
    int veces = 0;
    int vez = 0;
    int & vezActual = vez;

    veces = grados/45;

    for(int i = 0; i < size; i++){        //Ponemos las x en donde son sin rotaciones
        if(xInicialObjeto-listaActualPuntos->getPunto(i)->getX() <= xInicialObjeto){
            posX = x + (xInicialObjeto-listaActualPuntos->getPunto(i)->getX())*-1;
        } else{
            posX = x - xInicialObjeto-listaActualPuntos->getPunto(i)->getX();
        }

        if(yInicialObjeto-listaActualPuntos->getPunto(i)->getY() <= yInicialObjeto){
            posY = y + (yInicialObjeto-listaActualPuntos->getPunto(i)->getY())*-1;
        } else{
            posY = y - yInicialObjeto-listaActualPuntos->getPunto(i)->getY();
        }
    }

    //girar45(size, x, y, xInicialObjeto, yInicialObjeto, posX, posY, listaActualPuntos, veces, vezActual, id, objeto, letra, color);

}

Nodo_Objeto* menuEditarNivel2::girar45(Nodo_Nivel* nivelActual, int size, int x, int y, int xInicialObjeto, int yInicialObjeto,int posX, int posY,
                                       Lista_Puntos* listaActualPuntos, int veces, int &vezActual, int id, string objeto,
                                       char letra, string color){
    int posNuevaX45;
    int posNuevaY45;

    for(int i = 0; i < size; i++){
        //Comenzamos a rotar
        if(i != 0){
            int diferenciaX = listaActualPuntos->getPunto(i)->getX() - xInicialObjeto;
            int diferenciaY = listaActualPuntos->getPunto(i)->getY() - yInicialObjeto;
            Nodo_Puntos* nodoPuntosActual = listaActualPuntos->getPunto(i);
            Nodo_Puntos* nodoSiguiente = listaActualPuntos->getPunto(i+1);
            Nodo_Puntos* nodoAnterior = listaActualPuntos->getPunto(i-1);

            //Rotaciones cuando esta inclinado 45 grados
            if(abs(diferenciaX) == abs(diferenciaY)){
                if(nodoAnterior!= NULL && nodoAnterior->getX() != nodoPuntosActual->getX()
                        && nodoAnterior->getY() == nodoPuntosActual->getY()){
                    if(diferenciaX < 0){
                        posNuevaX45 = x - abs(diferenciaX) + 1;
                        posNuevaY45 = y + abs(diferenciaX) + 1;
                    }if(diferenciaX > 0){
                        posNuevaX45 = x + abs(diferenciaX) + 1;
                        posNuevaY45 = y + abs(diferenciaX) - 1;
                    }
                }
                else if(diferenciaY > 0){ //El Nodo Actual esta a la derecha del inicio
                    if(diferenciaX > 0){ //Nodo Actual esta abajo (mayor)
                        posNuevaY45 = y;
                        posNuevaX45 = x + diferenciaX;
                    }
                    if(diferenciaX < 0){ //Nodo Actual esta arriba (menor)
                        posNuevaX45 = x;
                        posNuevaY45 = y + abs(diferenciaY);
                    }

                }
                else if(diferenciaY < 0){ //El Nodo Actual esta a la izquierda del inicio
                    if(diferenciaX > 0){ //Nodo Actual esta abajo (Mayor)
                        posNuevaY45 = y - abs(diferenciaY);
                        posNuevaX45 = x;
                    }
                    if(diferenciaX < 0){ //Nodo Actual esta arriba(menor)
                        posNuevaX45 = x - abs(diferenciaX);
                        posNuevaY45 = y;
                    }
                }

            }
            //Rotaciones cuando esta en algun plano x o y
            else if(diferenciaX == 0){
                if(diferenciaY > 0){
                    posNuevaY45 = y + abs(diferenciaY);
                    posNuevaX45 = x + abs(diferenciaY);
                }
                if(diferenciaY < 0){
                    posNuevaX45 = x - abs(diferenciaY);
                    posNuevaY45 = y - abs(diferenciaY);
                }
            }
            else if(diferenciaY == 0){
                if(diferenciaX > 0){
                    posNuevaY45 = y - abs(diferenciaX);
                    posNuevaX45 = x + abs(diferenciaX);
                }
                if(diferenciaX < 0){
                    posNuevaX45 = x - abs(diferenciaX);
                    posNuevaY45 = y + abs(diferenciaX);
                }
            }

        } else {
            posNuevaX45 = posX;
            posNuevaY45 = posY;
        }
       }
    if(vezActual >= veces){
        Nodo_Objeto* nodoAgregado = new Nodo_Objeto(id, objeto, letra, color, posNuevaX45, posNuevaY45);
        nivelActual->getMatriz()->add(nodoAgregado);
        return nodoAgregado;
    } else {
        vezActual++;
        girar45(nivelActual, size, x, y, xInicialObjeto, yInicialObjeto, posX, posY, listaActualPuntos, veces, vezActual, id, objeto, letra, color);
    }
}

void menuEditarNivel2::eliminarObjeto(Nodo_Nivel* nivelActual){
    nivelActual->getABB()->recorrerInorden(nivelActual->getABB()->getRaiz());

    int idObjeto;
    int sizeOfNodosObjeto;

    cout << "Seleccione Objeto a Borrar: ";
    cin >> idObjeto;

    sizeOfNodosObjeto = nivelActual->getABB()->getObjeto(idObjeto, nivelActual->getABB()->getRaiz())->getListaPuntos()->getSizeNodos();
    nivelActual->getMatriz()->eliminarObjeto(idObjeto, sizeOfNodosObjeto);


    nivelActual->getABB()->eliminarNodo(nivelActual->getABB()->getRaiz(), idObjeto);
    this->arbolObjetos->crearGrafica(this->proyecto->getName(), nivelActual->getId());
    graficarNivel(nivelActual->getId());

    imprimirEspacios(1);



}

void menuEditarNivel2::eliminarPared(Nodo_Nivel* nivelActual){
    int x1, x2, y1, y2;
    cout << endl << "Ingrese Coordenada X Inicio: ";
    cin >> x1;
    cout << endl << "Ingrese Coordenada Y Inicio: ";
    cin >> y1;
    cout << endl << "Ingrese Coordenada X Final: ";
    cin >> x2;
    cout << endl << "Ingrese Coordenada Y Final: ";
    cin >> y2;

    nivelActual->getMatriz()->eliminarParedes(x1, y1, x2, y2);
}

void menuEditarNivel2::copiarNivel(){
    Nodo_Nivel* nivelACopiar;
    Nodo_Nivel* nivelASobrescribir;

    int idNivelACopiar = 0;
    int idNivelASobreEscribir = 0;

    this->proyecto->getListaNiveles()->imprimirNiveles();
    cout << "Ingrese Nivel a Copiar: " ;
    cin >> idNivelACopiar;
    imprimirEspacios(2);

    this->proyecto->getListaNiveles()->imprimirNiveles();
    cout << "En que nivel quiere copiarlo? ";
    cin >> idNivelASobreEscribir;

    nivelASobrescribir = this->proyecto->getListaNiveles()->getNodo(idNivelASobreEscribir);

    nivelACopiar= this->proyecto->getListaNiveles()->getNodo(idNivelACopiar);
    Matriz* matrizCopiada = nivelACopiar->getMatriz()->copiarMatriz();

    //Nivel Copiando

    //    delete nivelASobrescribir; <<<<<<< Este me daba error y borraba la matriz y abb
    delete nivelASobrescribir->getMatriz(); //Si los llamo por separado no me da error
    delete nivelASobrescribir->getABB(); //

    nivelASobrescribir->setMatriz(matrizCopiada);
    nivelASobrescribir->setABB(nivelACopiar->getABB()->copiarEsteArbolPreOrden());
    nivelASobrescribir->setId(idNivelASobreEscribir);
    graficarNivel(nivelASobrescribir->getId());
}

void menuEditarNivel2::crearCantidadPisos(){

}

void menuEditarNivel2::moveObjeto(){

}

void menuEditarNivel2::mostrarOpciones(){


}
