#include <utilities.h>

void imprimirAsteriscos(int a){
    for(int i = 0; i < a; i++){
        cout << "*";
    }
}

void imprimirEncabezado(){

    string encabezados[] = {"USAC","ESTRUCTURA DE DATOS", "SECCION: A", "OSCAR DARIEL LOPEZ MARTINEZ", "201621341"};

    imprimirAsteriscos(20);
    for(int i = 0; i < 5 ; i++){
        cout << endl;
        imprimirAsteriscos(1);
        cout << encabezados[i];
        imprimirAsteriscos(1);
    }
    cout << endl;
    imprimirAsteriscos(20);
    cout << endl;
}

void clearScreen(){
    cout << "\033[2J\033[1;1H";
}

void imprimirEspacios(int n){
    for(int i = 0; i < n; i++){
        cout << "\n";
    }
}
