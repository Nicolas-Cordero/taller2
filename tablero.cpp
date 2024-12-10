#include "tablero.hpp"
#include "nodo.hpp"
#include <vector>
using namespace std;



tablero::tablero(char jugadorActualIngresado)
{ // constructor
    matriz = vector<vector<char>>(3, vector<char>(3, ' '));
    jugadorActual = jugadorActualIngresado;
    juegoTerminado = false;
}
bool tablero::getJuegoTerminado()
{ // get juego terminado
    return juegoTerminado;
}
void tablero::setJuegoTerminado(bool estado)
{ // set juego terminado
    juegoTerminado = estado;
}
char tablero::getCasilla(int fila, int columna)
{ // get dato dada posicion
    return matriz[fila][columna];
}
void tablero::setCasilla(int fila, int columna, char dato)
{ // set dato dada posicion
    matriz[fila][columna] = dato;
}
int tablero::getSize()
{ // get size
    return matriz.size();
}
void tablero::imprimirTablero()
{ /// funcion 1, imprimir tablero
    cout << "    A   B   C" << endl;
    cout << "  +---+---+---+" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i << " |" << " ";
        for (int j = 0; j < 3; j++)
        {
            cout << matriz[i][j];
            cout << " | ";
        }
        cout << endl;
        cout << "  +---+---+---+" << endl;
    }
}
int tablero::contarEspaciosVacios()
{ 
    int contador = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matriz[i][j] == ' ')
            {
                contador++;
            }
        }
    }
    return contador;
}

int tablero::calcularPuntaje()

// se puede retornar 10, -10, 0 o -1 
// 0 si es empate, -1 si el juego no ha terminado

{
    // horizontal
    if (matriz[0][0] == matriz[0][1] && matriz[0][1] == matriz[0][2] && matriz[0][1]!= ' ')
    {
        return matriz[0][0] == jugadorActual ? 10 : -10;
    }
    if (matriz[1][0] == matriz[1][1] && matriz[1][1] == matriz[1][2] && matriz[1][1]!= ' ')
    {
        return matriz[1][0] == jugadorActual ? 10 : -10;
    }
    if (matriz[2][0] == matriz[2][1] && matriz[2][1] == matriz[2][2] && matriz[2][1]!= ' ')
    {
        return matriz[2][0] == jugadorActual ? 10 : -10;
    }

    // vertical
    if (matriz[0][0] == matriz[1][0] && matriz[1][0] == matriz[2][0] && matriz[1][0]!= ' ')
    {
        return matriz[0][0] == jugadorActual ? 10 : -10;
    }
    if (matriz[0][1] == matriz[1][1] && matriz[1][1] == matriz[2][1] && matriz[1][1]!= ' ')
    {
        return matriz[0][1] == jugadorActual ? 10 : -10;
    }
    if (matriz[0][2] == matriz[1][2] && matriz[1][2] == matriz[2][2] && matriz[1][2]!= ' ')
    {
        return matriz[0][2] == jugadorActual ? 10 : -10;
    }


    // diagonal 1
    if (matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2] && matriz[1][1]!= ' ')
    {
        return matriz[0][0] == jugadorActual ? 10 : -10;
    }
    // diagonal 2
    if (matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0] && matriz[1][1]!= ' ')
    {
        return matriz[0][2] == jugadorActual ? 10 : -10;
    }

    // empate

    if (tableroLleno()){
        return 0;
    }

    else{
        // el juego no ha terminado
        return -1;
    }
}

bool tablero::tableroLleno()
{ /// funcion 4, tablero lleno
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matriz[i][j] == ' ')
            {

                return false;
            }
        }
    }
    juegoTerminado = true;
    return true;
}
void tablero::cambiarJugador()
{ /// funcion 5, cambiar jugador
    if (jugadorActual == 'X')
    {
        jugadorActual = 'O';
        oponente = 'X';
    }
    else
    {
        jugadorActual = 'X';
        oponente = 'O';
    }
}
char tablero::getJugadorActual()
{ /// funcion 6, obtener jugador actual
    return jugadorActual;
}
char tablero::getOponente()
{ /// funcion 6.1, obtener oponente
    return oponente;
}
void tablero::reiniciarTablero()
{ /// funcion 7, reiniciar tablero
    matriz = vector<vector<char>>(3, vector<char>(3, ' '));
}
bool tablero::compararCon(tablero otroTablero)  {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->getCasilla(i, j) != otroTablero.getCasilla(i, j)) {
                return false;
            }
        }
    }
    return true;
}

