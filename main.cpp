#include "tablero.cpp"
#include <iostream>
#include <limits>
using namespace std;





pair<pair<int, int>, int> minimax(tablero t, int depth) {
    int puntaje = t.calcularPuntaje(); // Calcula el puntaje del tablero

    // Caso base: el juego ha terminado
    if (puntaje == 10 || puntaje == -10) {
        return {{-1, -1}, puntaje}; // Retorna puntaje terminal
    } else if (t.tableroLleno()) {
        return {{-1, -1}, 0}; // Retorna empate
    }

    pair<int, int> mejorMovimiento;
    int mejorPuntaje;

    // Inicializar dependiendo del jugador actual
    if (t.getJugadorActual() == 'X') {
        mejorPuntaje = -10000; // Inicializamos a un valor bajo para maximizar
    } else {
        mejorPuntaje = 10000; // Inicializamos a un valor alto para minimizar
    }

    // Explorar todos los movimientos posibles
    for (int i = 0; i < t.getSize(); i++) {
        for (int j = 0; j < t.getSize(); j++) {
            if (t.getCasilla(i, j) == ' ') { // Casilla vacía
                tablero tCopia = t;         // Crear copia del tablero
                tCopia.setCasilla(i, j, tCopia.getJugadorActual()); // Realizar movimiento
                tCopia.cambiarJugador();    // Cambiar turno

                // Evaluar el movimiento recursivamente
                int resultado = minimax(tCopia, depth + 1).second;

                if (t.getJugadorActual() == 'X') { // Maximizar
                    if (resultado > mejorPuntaje) {
                        mejorPuntaje = resultado;
                        mejorMovimiento = {i, j};
                    }
                } else { // Minimizar
                    if (resultado < mejorPuntaje) {
                        mejorPuntaje = resultado;
                        mejorMovimiento = {i, j};
                    }
                }
            }
        }
    }

    // Retornar el mejor movimiento y su puntaje asociado
    return {mejorMovimiento, mejorPuntaje};
}





int conversorSimpleLetra(char letra)
{
    if (letra == 'A' || letra == 'a')
    {
        return 0;
    }
    if (letra == 'B' || letra == 'b')
    {
        return 1;
    }
    if (letra == 'C' || letra == 'c')
    {
        return 2;
    }
    return -1;
}

char conversorSimpleNumero(int num)
{
    if (num == 0)
    {
        return 'A';
    }
    if (num == 1)
    {
        return 'B';
    }
    if (num == 2)
    {
        return 'C';
    }
    
    return -1;
}

int pvia(){

}

int pvp()
{
    tablero t('X');
    t.imprimirTablero();
    int fila, columna;
    int puntajeActual;
    char columnaChar;
    while (true)
    {
        cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
        cin >> columnaChar;
        columna = conversorSimpleLetra(columnaChar);
        while (columna == -1)
        {
            cout << "Columna invalida, intente de nuevo" << endl;
            cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
            cin >> columnaChar;
            columna = conversorSimpleLetra(columnaChar);
        }
        cout << "Jugador " << t.getJugadorActual() << " ingrese la FILA (0, 1 o 2): ";
        cin >> fila;
        while (fila < 0 || fila > 2)
        {
            cout << "Fila invalida, intente de nuevo" << endl;
            cout << "Jugador " << t.getJugadorActual() << " ingrese la FILA (0, 1 o 2): ";
            cin >> fila;
        }

        t.setCasilla(fila, columna, t.getJugadorActual());
        
        t.imprimirTablero();
        puntajeActual = t.calcularPuntaje();
        if (puntajeActual == 10 || puntajeActual == -10)
        {
            cout << "Jugador " << t.getJugadorActual() << " ha ganado!" << endl;
            break;
        }
        else if (puntajeActual == 0)
        {
            cout << "Empate!" << endl;
            break;
        }
        t.cambiarJugador();
        pair<pair<int,int>,int> outPutMiniMax = minimax(t, 0);
        cout << "Mejor jugada sugerida por minimaxNuevo: (" << 
        outPutMiniMax.first.first << ", " << conversorSimpleNumero(outPutMiniMax.first.second) << ")" << endl;

        
        
    }
    return 0;
}

int main()
{
    bool mainMenuBool = true;
    int mainMenuSelect;
    while (mainMenuBool)
    {
        cout << "Bienvenido al programa!" << endl;
        cout << "+---+---+---+---+---+" << endl;
        cout << "Menu Principal:" << endl;
        cout << "1. Player vs Player" << endl;
        cout << "2. Player vs IA" << endl;
        cout << "3. Salir" << endl;
        cout << "+---+---+---+---+---+" << endl;
        cin >> mainMenuSelect;
        switch (mainMenuSelect)
        {

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