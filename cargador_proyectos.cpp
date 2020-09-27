#include "cargador_proyectos.h"

Cargador_Proyectos::Cargador_Proyectos()
{

}

//Metodo para agregar Proyectos

Arbol_AVL* Cargador_Proyectos::cargarNuevo(string nombreArchivo, Arbol_Binario* arbolBinario){
    int numeroProyectos = 0;
    int numeroNiveles = 0;

    Arbol_AVL* nuevo = new Arbol_AVL();
    Arbol_Binario* abbActual = arbolBinario;

    json j;

    try {
        string archivo= nombreArchivo + ".json";
        ifstream reader;
        reader.open(archivo);
        reader>>j;
        reader.close();
        cout << endl << "Proyectos Cargados exitosamente" << endl;
    } catch (exception e) {
        cout << e.what();
        cout << endl << "Archivo no Encontrado" << endl;
    }

    numeroProyectos = j["proyectos"].size();
    cout << "Proyectos: " << numeroProyectos << endl;

    for(int i = 0; i < numeroProyectos; i++){//i = numero de proyecto

        //Cargar Niveles
        Lista_Niveles* nuevaListaNiveles = cargarNiveles(j, i, abbActual);


        //Insertar Nodo Proyectos
        cout << "Insertando: " << (j["proyectos"][i]["nombre"]) << endl;
        nuevo->insertar(j["proyectos"][i]["nombre"], nuevaListaNiveles, i+1, abbActual);
        cout << "Done" << endl;
    }

    return nuevo;

}

Lista_Niveles* Cargador_Proyectos::cargarNiveles(json jasonFile, int numeroProyecto, Arbol_Binario *abbActual){

    //****Imprimimos cantidad de Niveles
    int numeroNiveles = jasonFile["proyectos"][numeroProyecto]["niveles"].size();
    cout << "Niveles:" << numeroNiveles << endl;

    Lista_Niveles* listaNiveles = new Lista_Niveles();

    for(int j = 0; j < numeroNiveles; j++){ // j = numero nivel
        Arbol_Binario* nuevoABB = new Arbol_Binario();
        //Cargar Arbol Binario
        if(abbActual == NULL){
            abbActual = cargarLibreriasNivel(jasonFile, numeroProyecto, j);
        } else {
            //Comparar si tenemos los mismo objetos, si no los tenemos, agregarlo al abbActual
            agregarObjetosExtra(jasonFile, abbActual, numeroProyecto, j); //j = numero nivel
            //Cremos nuevo ABB y lo agregamos al nivel (Cada nivel tiene su propio ABB)
            agregarObjetosExtra(jasonFile, nuevoABB, numeroProyecto, j);
        }

        Matriz* nuevaMatriz = crearMatriz(jasonFile, numeroProyecto, j, abbActual);
        int idNivel = jasonFile["proyectos"][numeroProyecto]["niveles"][j]["nivel"];

        Nodo_Nivel* nodoNivel = new Nodo_Nivel(idNivel, nuevaMatriz, nuevoABB);

        cout << "Insertando Nivel: " << jasonFile["proyectos"][numeroProyecto]["niveles"][j]["nivel"] << endl;

        listaNiveles->addNode(nodoNivel);
    }
    return listaNiveles;
}


Matriz* Cargador_Proyectos::crearMatriz(json jasonFile, int numeroProyecto, int numeroNivel, Arbol_Binario *abbActual){
    int numeroParedes = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["paredes"].size();
    int numeroVentanas = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["ventanas"].size();
    int numeroObjetos = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"].size();

    Matriz* nuevaMatriz = new Matriz();

    //Agregar paredes
    for(int i = 0; i<numeroParedes; i++){
        int xInicial = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["paredes"][i]["inicio"][0];
        int yInicial = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["paredes"][i]["inicio"][1];

        int xFinal = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["paredes"][i]["final"][0];
        int yFinal = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["paredes"][i]["final"][1];

        string color = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["paredes"][i]["color"];

        //int actualX = x;
        //int actualY = y;

        if(xInicial < xFinal){
            for(int x = xInicial; x< xFinal+1; x++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*10000+x, "Pared", 'P', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        } else if (xInicial > xFinal){
            for(int x = xInicial; x< xFinal-1; x--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*10000+x, "Pared", 'P', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        }    //Lista_Niveles* getListaNiveles();


        if(yInicial < yFinal){
            for(int y = yInicial; y< yFinal+1; y++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*20000+y, "Pared", 'P', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        } else if (yInicial > yFinal){
            for(int y = yInicial; y< yFinal-1; y--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*20000+y, "Pared", 'P', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        }
    }

    //Agregar Objetos
    for(int i = 0; i<numeroObjetos; i++){

        int numeroCoordenadas = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][i]["puntos"].size();

        for(int k = 0; k < numeroCoordenadas ; k++){
            int xObjeto = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][i]["puntos"][k]["x"];
            int yObjeto = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][i]["puntos"][k]["y"];

            int id = (jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][i]["identificador"]);
            string nombreObjeto = (jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][i]["nombre"]);
            string caracter = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][i]["letra"];
            string color = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][i]["color"];

            char letra[caracter.size() + 1];
            strcpy(letra, caracter.c_str()); //Convertimos string a char

            Nodo_Objeto* nuevoObjeto = new Nodo_Objeto(id, nombreObjeto, letra[0], color, xObjeto, yObjeto);

            nuevaMatriz->add(nuevoObjeto);
        }
        nuevaMatriz->sumarCantidadObjeto();

    }

    //Agregar Ventanas
    for(int i = 0; i<numeroVentanas; i++){
        int xInicial = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["ventanas"][i]["inicio"][0];
        int yInicial = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["ventanas"][i]["inicio"][1];

        int xFinal = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["ventanas"][i]["final"][0];
        int yFinal = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["ventanas"][i]["final"][1];

        string color = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["ventanas"][i]["color"];

        //int actualX = x;
        //int actualY = y;0

        if(xInicial < xFinal){
            for(int x = xInicial; x< xFinal+1; x++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*100000+x, "ventana", 'V', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        } else if (xInicial > xFinal){
            for(int x = xInicial; x< xFinal-1; x--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*100000+x, "Ventana", 'V', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        }    //Lista_Niveles* getListaNiveles();


        if(yInicial < yFinal){
            for(int y = yInicial; y< yFinal+1; y++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*200000+y, "Ventana", 'V', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        } else if (yInicial > yFinal){
            for(int y = yInicial; y< yFinal-1; y--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*200000+y, "Ventana", 'V', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        }
    }

    return nuevaMatriz;
}

Arbol_Binario* Cargador_Proyectos::cargarLibreriasNivel(json jasonFile, int numeroProyecto, int numeroNivel){
    int numeroObjetos = 0;
    Arbol_Binario* nuevo = new Arbol_Binario();

    numeroObjetos = jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"].size();
    cout << "Cantidad Objetos: " << numeroObjetos << endl;

    for(int indiceObjeto = 0; indiceObjeto < numeroObjetos; indiceObjeto++){ //i = indice De Objeto

        Lista_Puntos* nuevaListaPuntos = cargarCoordenadasObjetosProyecto(jasonFile, numeroProyecto, numeroNivel, indiceObjeto);

        int id = (jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][indiceObjeto]["identificador"]);
        string nombreObjeto = (jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][indiceObjeto]["nombre"]);
        string color = (jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][indiceObjeto]["color"]);

        string caracter = (jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][indiceObjeto]["letra"]);

        char letra[caracter.size() + 1];
        strcpy(letra, caracter.c_str()); //Convertimos string a char

        nuevo->insertar(id, nombreObjeto, letra[0], color, nuevaListaPuntos); //(int id, string nombre, char letra, string color, Lista_Puntos* xy

        cout << "Insertando: " << (jasonFile["proyectos"][numeroProyecto]["niveles"][numeroNivel]["objetos"][indiceObjeto]["nombre"]) << endl;
        cout << "Done" << endl;
    }

    return nuevo;
}

Lista_Puntos* Cargador_Proyectos::cargarCoordenadasObjetosProyecto(json jasonFile, int indiceProyecto, int indiceNivel, int indiceObjeto){

    //****Imprimimos cantidad de Coordenadas
    int numeroCoordenadas = jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][indiceObjeto]["puntos"].size();
    cout << "#Coordenadas:" << numeroCoordenadas << endl;
    //****Imprimimos cantidad de Coordenadas

    Lista_Puntos* nuevaListaPuntos = new Lista_Puntos();

    for(int j = 0; j < numeroCoordenadas; j++){

        int xEnJason = jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][indiceObjeto]["puntos"][j]["x"];
        int yEnJason = jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][indiceObjeto]["puntos"][j]["y"];

        Nodo_Puntos* nodoXY = new Nodo_Puntos(xEnJason, yEnJason);
        nodoXY->setSiguiente(NULL);

        cout << "Insertando Coordenadas: " << xEnJason << ", " << yEnJason << endl;

        nuevaListaPuntos->addNode(nodoXY);
    }
    return nuevaListaPuntos;
}

//Cargar Librerias y Cargar Librerias de Nivel
Arbol_Binario* Cargador_Proyectos::cargarLibrerias(string nombreArchivo){
    int numeroObjetos = 0;
    int numeroCoordenadas = 0;
    Arbol_Binario* nuevo = new Arbol_Binario();
    bool archivoEncontrado = false;
    json j;

    try {
        string archivo= nombreArchivo + ".json";
        ifstream reader(archivo);
        reader>>j;
        reader.close();
        cout << endl << "Objetos Cargados exitosamente" << endl;
        archivoEncontrado = true;
    } catch (exception e) {
        cout << e.what();
        cout << endl << "Archivo no Encontrado" << endl;
        archivoEncontrado = false;
    }

    if(archivoEncontrado){
        numeroObjetos = j["Libreria"].size();
        cout << "Cantidad Objetos: " << numeroObjetos << endl;

        for(int i = 0; i < numeroObjetos; i++){ //i = indice De Objeto

            Lista_Puntos* nuevaListaPuntos = cargarCoordenadas(j, i);

            int id = (j["Libreria"][i]["identificador"]);
            string nombreObjeto = (j["Libreria"][i]["nombre"]);
            string color = (j["Libreria"][i]["color"]);


            string caracter = (j["Libreria"][i]["letra"]);


            char letra[caracter.size() + 1];
            strcpy(letra, caracter.c_str()); //Convertimos string a char

            nuevo->insertar(id, nombreObjeto, letra[0], color, nuevaListaPuntos); //(int id, string nombre, char letra, string color, Lista_Puntos* xy

            cout << "Insertando: " << (j["Libreria"][i]["nombre"]) << endl;
            cout << "Done" << endl;
        }


    }
    else {
        return NULL;
    }
    return nuevo;

}

Lista_Puntos* Cargador_Proyectos::cargarCoordenadas(json jasonFile, int indiceObjeto){

    //****Imprimimos cantidad de Coordenadas
    int numeroCoordenadas = jasonFile["Libreria"][indiceObjeto]["puntos"].size();
    cout << "#Coordenadas:" << numeroCoordenadas << endl;
    //****Imprimimos cantidad de Coordenadas


    Lista_Puntos* nuevaListaPuntos = new Lista_Puntos();

    for(int j = 0; j < numeroCoordenadas; j++){

        int xEnJason = jasonFile["Libreria"][indiceObjeto]["puntos"][j]["x"];
        int yEnJason = jasonFile["Libreria"][indiceObjeto]["puntos"][j]["y"];

        Nodo_Puntos* nodoXY = new Nodo_Puntos(xEnJason, yEnJason);

        cout << "Insertando Coordenadas: " << xEnJason << ", " << yEnJason << endl;

        nuevaListaPuntos->addNode(nodoXY);
    }
    return nuevaListaPuntos;
}

void Cargador_Proyectos::agregarObjetosExtra(json jasonFile, Arbol_Binario* arbolActual, int indiceProyecto, int indiceNivel){
    int numeroObjetos = 0;

    numeroObjetos = jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"].size();
    cout << "Cantidad Objetos: " << numeroObjetos << endl;

    for(int i = 0; i < numeroObjetos; i++){ //i = indice De Objeto

        Lista_Puntos* nuevaListaPuntos = cargarCoordenadasObjetosProyecto(jasonFile, indiceProyecto, indiceNivel, i);

        int id = (jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][i]["identificador"]);
        string nombreObjeto = (jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][i]["nombre"]);
        string color = (jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][i]["color"]);
        string caracter = (jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][i]["letra"]);

        char letra[caracter.size() + 1];
        strcpy(letra, caracter.c_str()); //Convertimos string a char

        //Agregar
        arbolActual->insertar(id, nombreObjeto, letra[0], color, nuevaListaPuntos); //(int id, string nombre, char letra, string color, Lista_Puntos* xy

        cout << "Insertando Extra: " << (jasonFile["proyectos"][indiceProyecto]["niveles"][indiceNivel]["objetos"][i]["nombre"]) << endl;
        cout << "Done" << endl;
    }
}

//Metodos para Agregar Nivel Extra a Lista de Niveles

void Cargador_Proyectos::agregarNivelExtra(Lista_Niveles *listaActual, Arbol_Binario *arbolObjetos, string nombreArchivo){
    int numeroNiveles = 0;

    Arbol_AVL* nuevo = new Arbol_AVL();
    Arbol_Binario* abbActual = arbolObjetos;

    json jasonFile;


    try {
        string archivo= nombreArchivo + ".json";
        ifstream reader(archivo);
        reader>>jasonFile;
        reader.close();
        cout << endl << "Niveles Cargados exitosamente" << endl;
    } catch (exception e) {
        cout << e.what();
        cout << endl << "Archivo no Encontrado" << endl;
    }

    numeroNiveles = jasonFile["niveles"].size();
    cout << "#Niveles a Agregar: " << numeroNiveles<< endl;

    Lista_Niveles* listaNiveles = new Lista_Niveles();

    //A
    for(int j = 0; j < numeroNiveles; j++){
        Arbol_Binario* nuevoABB = new Arbol_Binario();
        // j = numero nivel
        //Cargar Arbol Binario
        if(abbActual == NULL){
            abbActual = cargarLibreriasNivelExtra(jasonFile,  j);
        } else {
            //Comparar si tenemos los mismo objetos, si no los tenemos, agregarlo al abbActual
            agregarObjetosExtraNivelExtra(jasonFile, abbActual, j); //j = numero nivel

            //Cremos nuevo ABB y lo agregamos al nivel (Cada nivel tiene su propio ABB)
            agregarObjetosExtraNivelExtra(jasonFile, nuevoABB, j);
        }


        Matriz* nuevaMatriz = crearMatrizNivelExtra(jasonFile, j);
        int idNivel = jasonFile["niveles"][j]["nivel"];

        Nodo_Nivel* nodoNivel = new Nodo_Nivel(idNivel, nuevaMatriz, nuevoABB);

        cout << "Insertando Nivel: " << jasonFile["niveles"][j]["nivel"] << endl;

        listaActual->addNode(nodoNivel);
    }
}

Arbol_Binario* Cargador_Proyectos::cargarLibreriasNivelExtra(json jasonFile, int numeroNivel){
    int numeroObjetos = 0;
    Arbol_Binario* nuevo = new Arbol_Binario();

    numeroObjetos = jasonFile["niveles"][numeroNivel]["objetos"].size();
    cout << "Cantidad Objetos: " << numeroObjetos << endl;

    for(int indiceObjeto = 0; indiceObjeto < numeroObjetos; indiceObjeto++){ //i = indice De Objeto

        Lista_Puntos* nuevaListaPuntos = cargarCoordenadasObjetosExtraNivel(jasonFile, numeroNivel, indiceObjeto);

        int id = (jasonFile["niveles"][numeroNivel]["objetos"][indiceObjeto]["identificador"]);
        string nombreObjeto = (jasonFile["niveles"][numeroNivel]["objetos"][indiceObjeto]["nombre"]);
        string color = (jasonFile["niveles"][numeroNivel]["objetos"][indiceObjeto]["color"]);

        string caracter = (jasonFile["niveles"][numeroNivel]["objetos"][indiceObjeto]["letra"]);

        char letra[caracter.size() + 1];
        strcpy(letra, caracter.c_str()); //Convertimos string a char

        nuevo->insertar(id, nombreObjeto, letra[0], color, nuevaListaPuntos); //(int id, string nombre, char letra, string color, Lista_Puntos* xy

        cout << "Insertando: " << (jasonFile["niveles"][numeroNivel]["objetos"][indiceObjeto]["nombre"]) << endl;
        cout << "Done" << endl;
    }

    return nuevo;
}


void Cargador_Proyectos::agregarObjetosExtraNivelExtra(json jasonFile, Arbol_Binario* arbolActual, int indiceNivel){
    int numeroObjetos = 0;

    numeroObjetos = jasonFile["niveles"][indiceNivel]["objetos"].size();
    cout << "Cantidad Objetos: " << numeroObjetos << endl;

    for(int i = 0; i < numeroObjetos; i++){ //i = indice De Objeto

        Lista_Puntos* nuevaListaPuntos = cargarCoordenadasObjetosExtraNivel(jasonFile, indiceNivel, i);

        int id = (jasonFile["niveles"][indiceNivel]["objetos"][i]["identificador"]);
        string nombreObjeto = (jasonFile["niveles"][indiceNivel]["objetos"][i]["nombre"]);
        string color = (jasonFile["niveles"][indiceNivel]["objetos"][i]["color"]);
        string caracter = (jasonFile["niveles"][indiceNivel]["objetos"][i]["letra"]);

        char letra[caracter.size() + 1];
        strcpy(letra, caracter.c_str()); //Convertimos string a char

        //Agregar
        arbolActual->insertar(id, nombreObjeto, letra[0], color, nuevaListaPuntos); //(int id, string nombre, char letra, string color, Lista_Puntos* xy

        cout << "Insertando Extra: " << (jasonFile["niveles"][indiceNivel]["objetos"][i]["nombre"]) << endl;
        cout << "Done" << endl;
    }

}

Lista_Puntos* Cargador_Proyectos::cargarCoordenadasObjetosExtraNivel(json jasonFile, int indiceNivel, int indiceObjeto){

    //****Imprimimos cantidad de Coordenadas
    int numeroCoordenadas = jasonFile["niveles"][indiceNivel]["objetos"][indiceObjeto]["puntos"].size();
    cout << "#Coordenadas:" << numeroCoordenadas << endl;
    //****Imprimimos cantidad de Coordenadas

    Lista_Puntos* nuevaListaPuntos = new Lista_Puntos();

    for(int j = 0; j < numeroCoordenadas; j++){

        int xEnJason = jasonFile["niveles"][indiceNivel]["objetos"][indiceObjeto]["puntos"][j]["x"];
        int yEnJason = jasonFile["niveles"][indiceNivel]["objetos"][indiceObjeto]["puntos"][j]["y"];

        Nodo_Puntos* nodoXY = new Nodo_Puntos(xEnJason, yEnJason);
        nodoXY->setSiguiente(NULL);

        cout << "Insertando Coordenadas: " << xEnJason << ", " << yEnJason << endl;

        nuevaListaPuntos->addNode(nodoXY);
    }
    return nuevaListaPuntos;
}

Matriz* Cargador_Proyectos::crearMatrizNivelExtra(json jasonFile, int numeroNivel){
    int numeroParedes = jasonFile["niveles"][numeroNivel]["paredes"].size();
    int numeroObjetos = jasonFile["niveles"][numeroNivel]["objetos"].size();
    int numeroVentanas = jasonFile["niveles"][numeroNivel]["ventanas"].size();

    Matriz* nuevaMatriz = new Matriz();

    //Coordenadas de Inicio
    //Agregar Paredes
    for(int i = 0; i<numeroParedes; i++){
        int xInicial = jasonFile["niveles"][numeroNivel]["paredes"][i]["inicio"][0];
        int yInicial = jasonFile["niveles"][numeroNivel]["paredes"][i]["inicio"][1];

        int xFinal = jasonFile["niveles"][numeroNivel]["paredes"][i]["final"][0];
        int yFinal = jasonFile["niveles"][numeroNivel]["paredes"][i]["final"][1];

        string color = jasonFile["niveles"][numeroNivel]["paredes"][i]["color"];

        //int actualX = x;
        //int actualY = y;

        if(xInicial < xFinal){
            for(int x = xInicial; x< xFinal+1; x++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*10000+x, "Pared", 'P', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        } else if (xInicial > xFinal){
            for(int x = xInicial; x< xFinal-1; x--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*10000+x, "Pared", 'P', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        }    //Lista_Niveles* getListaNiveles();


        if(yInicial < yFinal){
            for(int y = yInicial; y< yFinal+1; y++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*20000+y, "Pared", 'P', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        } else if (yInicial > yFinal){
            for(int y = yInicial; y< yFinal-1; y--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*20000+y, "Pared", 'P', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        }
    }

    //Agregar Objetos
    for(int i = 0; i<numeroObjetos; i++){
        int numeroCoordenadas = jasonFile["niveles"][numeroNivel]["objetos"][i]["puntos"].size();
        for(int k = 0; k < numeroCoordenadas ; k++){
            int xObjeto = jasonFile["niveles"][numeroNivel]["objetos"][i]["puntos"][k]["x"];
            int yObjeto = jasonFile["niveles"][numeroNivel]["objetos"][i]["puntos"][k]["y"];


            int id = (jasonFile["niveles"][numeroNivel]["objetos"][i]["identificador"]);
            string nombreObjeto = (jasonFile["niveles"][numeroNivel]["objetos"][i]["nombre"]);
            string caracter = jasonFile["niveles"][numeroNivel]["objetos"][i]["letra"];
            string color = jasonFile["niveles"][numeroNivel]["objetos"][i]["color"];

            char letra[caracter.size() + 1];
            strcpy(letra, caracter.c_str()); //Convertimos string a char

            Nodo_Objeto* nuevoObjeto = new Nodo_Objeto(id, nombreObjeto, letra[0], color, xObjeto, yObjeto);
            nuevaMatriz->add(nuevoObjeto);
        }
        nuevaMatriz->sumarCantidadObjeto();
    }

    //Agregar Ventanas
    for(int i = 0; i<numeroVentanas; i++){
        int xInicial = jasonFile["niveles"][numeroNivel]["ventanas"][i]["inicio"][0];
        int yInicial = jasonFile["niveles"][numeroNivel]["ventanas"][i]["inicio"][1];

        int xFinal = jasonFile["niveles"][numeroNivel]["ventanas"][i]["final"][0];
        int yFinal = jasonFile["niveles"][numeroNivel]["ventanas"][i]["final"][1];

        string color = jasonFile["niveles"][numeroNivel]["ventanas"][i]["color"];

        //int actualX = x;
        //int actualY = y;0

        if(xInicial < xFinal){
            for(int x = xInicial; x< xFinal+1; x++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*100000+x, "ventana", 'V', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        } else if (xInicial > xFinal){
            for(int x = xInicial; x< xFinal-1; x--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*100000+x, "Ventana", 'V', color, x, yInicial);
                nuevaMatriz->add(nuevo);
            }
        }    //Lista_Niveles* getListaNiveles();


        if(yInicial < yFinal){
            for(int y = yInicial; y< yFinal+1; y++){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*200000+y, "Ventana", 'V', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        } else if (yInicial > yFinal){
            for(int y = yInicial; y< yFinal-1; y--){
                Nodo_Objeto *nuevo = new Nodo_Objeto((i+1)*200000+y, "Ventana", 'V', color, xInicial, y);
                nuevaMatriz->add(nuevo);
            }
        }
    }


    return nuevaMatriz;
}

