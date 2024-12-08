#include "tablero.cpp"
#include <iostream>
using namespace std;

int conversorSimpleLetra(char letra){
    if (letra == 'A' || letra == 'a'){
        return 0;
    }
    if (letra == 'B' || letra == 'b'){
        return 1;
    }
    if (letra == 'C' || letra == 'c'){
        return 2;
    }
    return -1;
}

int pvp(){
    tablero t;
    t.imprimirTablero();
    int fila, columna;
    char columnaChar;
    while (true){
        cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
        cin >> columnaChar;
        columna = conversorSimpleLetra(columnaChar);
        cout << "Jugador " << t.getJugadorActual() << " ingrese la FILA (0, 1 o 2): ";
        cin >> fila;
        

        if (t.hacerMovimiento(fila, columna)){
            t.imprimirTablero();
            if (t.hayGanador()){
                cout << "Jugador " << t.getJugadorActual() << " ha ganado!" << endl;
                break;
            }
            if (t.tableroLleno()){
                cout << "Empate!" << endl;
                break;
            }
            t.cambiarJugador();
        }
        else{
            cout << "Movimiento invalido, intente de nuevo" << endl;
        }
    }
    return 0;
}

int main() {
    bool mainMenuBool = true;
    int mainMenuSelect;
    while (mainMenuBool){
        cout << "Bienvenido al programa!" << endl;
        cout << "+---+---+---+---+---+" << endl;
        cout << "Menu Principal:"  << endl;
        cout << "1. Player vs Player" << endl;
        cout << "2. Player vs IA" << endl;
        cout << "3. Salir" << endl; 
        cout << "+---+---+---+---+---+" << endl;
        cin >> mainMenuSelect;
        switch (mainMenuSelect) {
        
        case 1:
            cout << "+---+---+---+---+---+" << endl;
            cout << "-Player vs Player-" << endl;
            pvp();
            break;
        case 2:
            cout << "Player vs IA" << endl;
            break;
        case 3:
            cout << "Saliendo..." << endl;
            mainMenuBool = false;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    }
}