#include "tablero.cpp"
#include <iostream>
#include <limits>
using namespace std;

int minimax(tablero &t, int profundidad, bool esMax, int alpha, int beta){
    char jugador = esMax ? 'O' : 'X';
    char oponente = esMax ? 'X' : 'O';
    if(t.hayGanador() == oponente){
        return -10 + profundidad;
  
    }
    if(t.hayGanador() == jugador){
        return 10 - profundidad;
    }
    if(t.tableroLleno()){
        return 0;
    }

    int mejorPuntaje = esMax ? -10000 : 10000;

    for (int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if (t.getDato(i, j) == ' '){
                t.hacerMovimiento(i, j, jugador);
                int puntaje = minimax(t, profundidad + 1, !esMax, alpha, beta);
                t.hacerMovimiento(i, j, ' ');

                if (esMax){
                    mejorPuntaje = max(puntaje, mejorPuntaje);
                    alpha = max(alpha, puntaje);
                }
                else{
                    mejorPuntaje = min(puntaje, mejorPuntaje);
                    beta = min(beta, puntaje);
                }
                if (beta <= alpha){
                    break;
                }
            }
        }
    }
    return mejorPuntaje;
}

pair<int, int> obtenerMejorMovimiento(tablero &t){
    int mejorPuntaje = -10000; 
    pair<int, int> mejorMovimiento = {-1,-1};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (t.getDato(i, j) == ' '){
                t.hacerMovimiento(i, j, t.getOponente());
                int puntaje = minimax(t, 0 , false, -10000, 10000);
                t.hacerMovimiento(i, j, ' ');

                if (puntaje > mejorPuntaje){
                    mejorPuntaje = puntaje;
                    mejorMovimiento = {i, j};
                }
            }
        }
    }
    return mejorMovimiento;
}

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
        

        if (t.hacerMovimiento(fila, columna, ' ')){
            t.imprimirTablero();
            if (t.hayGanador() != ' '){
                cout << "Jugador " << t.getJugadorActual() << " ha ganado!" << endl;
                break;
            }
            if (t.tableroLleno()){
                cout << "Empate!" << endl;
                break;
            }
            t.cambiarJugador();
            cout << "--------------------------------" << endl;
            auto mejorMovimiento = obtenerMejorMovimiento(t);
            cout << "siguiente mejor movimiento";
            cout << "first: " << mejorMovimiento.first;
            cout << "second: " << mejorMovimiento.second;
            cout << "--------------------------------" << endl;
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