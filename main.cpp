#include "tablero.cpp"
#include <iostream>
#include <limits>
using namespace std;

int minimax2(tablero& t, const int& profundidad, const bool& max){
    int costo = t.calcularCostoTablero();
    if(profundidad == 9 || t.hayGanador() != ' '){
        return costo;
    }
    if (max){
        int maxEvaluar = -10000;
        
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(t.getDato(i, j) == ' '){
                    // populamos el tablero con el jugador actual
                    t.hacerMovimientoForzado(i, j, 'X');

                    maxEvaluar = std::max(maxEvaluar, minimax2(t, profundidad + 1, !max));
                   
                    t.setMovimiento(i, j, ' ');
                    t.setJuegoTerminado (false);
                }
            }
        }
        return maxEvaluar;
    }
    else{
        int minEvaluar = 10000;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(t.getDato(i, j) == ' '){
                    // populamos el tablero con el jugador actual
                    t.hacerMovimientoForzado(i, j, 'O');

                    minEvaluar = min(minEvaluar, minimax2(t, profundidad + 1, !max));
                    
                    t.setMovimiento(i, j, ' ');
                }
            }
        }
        return minEvaluar; 
    }
}

int minimax(tablero &t, int profundidad, bool esMax, int alpha, int beta){
    char ganador = t.hayGanador();
    char jugador = esMax ? 'O' : 'X';
    char oponente = esMax ? 'X' : 'O';
    if(ganador == oponente){
        return -10 - profundidad;
  
    }
    if(ganador == jugador){
        return 10 + profundidad;
    }
    if(t.tableroLleno()){
        return 0;
    }

    int mejorPuntaje = esMax ? -10000 : 10000;

    for (int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if (t.getDato(i, j) == ' '){
                t.hacerMovimientoForzado(i, j, jugador);
                int puntaje = minimax(t, profundidad + 1, !esMax, alpha, beta);
                t.hacerMovimientoForzado(i, j, ' ');

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
        //
        if (beta <= alpha){
            break;
        }
    }
    return mejorPuntaje;
}

char* obtenerMejorMovimiento2(tablero t){
    int minMaxEvaluar = t.getJugadorActual() == 'X' ? -10000 : 10000;
    char * mejorMovimiento = new char[3];
    // loop en todos los hijos desde la posicion actual
    for (int i= 0 ; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (t.getDato(i, j) == ' '){
                // hacemos el movimiento actual
                t.setMovimiento(i, j, t.getJugadorActual() ? 'x' : 'o');
                bool maxOrMin = t.getJugadorActual() == 'X' ? true : false;

                // evaluacion del movimiento con minimax
                int evaluar = minimax2(t, 0, maxOrMin);

                // deshacemos el movimiento
                t.setMovimiento(i, j, ' ');
                t.setJuegoTerminado(false);
                
                // obtenemos la maxima evaluacoin si el jugador es X
                if(t.getJugadorActual() == 'X'){
                    if (evaluar > minMaxEvaluar){
                        mejorMovimiento[0] = (char)(j + 'A');
                        mejorMovimiento[1] = (char)(i + '1');

                        minMaxEvaluar = evaluar;
                    }
                }
                // obtenemos la minima evaluacion si el jugador es O
                else{
                    if (evaluar < minMaxEvaluar){
                        mejorMovimiento[0] = (char)(j + 'A');
                        mejorMovimiento[1] = (char)(i + '1');
                        minMaxEvaluar = evaluar;
                    }
                }

            }
        }
    }
    mejorMovimiento[2] = '\0';
    return mejorMovimiento;

}


pair<int, int> obtenerMejorMovimiento(tablero &t){
    int mejorPuntaje = -10000; 
    pair<int, int> mejorMovimiento = {-1,-1};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (t.getDato(i, j) == ' '){
                t.hacerMovimientoForzado(i, j, t.getOponente());
                int puntaje = minimax(t, 0 , false, -10000, 10000);
                t.hacerMovimientoForzado(i, j, ' ');

                if (puntaje > mejorPuntaje){
                    mejorPuntaje = puntaje;
                    mejorMovimiento = {i, j};
                }
            }
        }
    }
    if (mejorMovimiento.first == -1 && mejorMovimiento.second == -1){
        cout << "no se encontró un movimiento válido" << endl;
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

int pvia(){
    tablero t;
    t.imprimirTablero();
    int fila, columna;
    char columnaChar;
    while (true){
        // Jugador
        cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
        cin >> columnaChar;
        columna = conversorSimpleLetra(columnaChar);
        while (columna == -1){
            cout << "Columna invalida, intente de nuevo" << endl;
            cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
            cin >> columnaChar;
        }
        cout << "Jugador " << t.getJugadorActual() << " ingrese la FILA (0, 1 o 2): ";
        cin >> fila;
        

        if (t.hacerMovimiento(fila, columna)){
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
            /// IA
            cout << "-*--*-Es el turno de la IA-*--*- " << endl;
            char* mejorMovimiento = obtenerMejorMovimiento2(t);
            cout << "La IA ha seleccionado la casilla: " << mejorMovimiento[0] << 
            "+" << mejorMovimiento[1] << "+" << mejorMovimiento[2] << endl;
            
        }
        else{
            cout << "Movimiento invalido, intente de nuevo" << endl;
        }
    }
    return 0;
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
        while (columna == -1){
            cout << "Columna invalida, intente de nuevo" << endl;
            cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
            cin >> columnaChar;
        }
        cout << "Jugador " << t.getJugadorActual() << " ingrese la FILA (0, 1 o 2): ";
        cin >> fila;
        

        if (t.hacerMovimiento(fila, columna)){
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
            cout << "+---+---+---+---+---+" << endl;
            cout << "Player vs IA" << endl;
            pvia();

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