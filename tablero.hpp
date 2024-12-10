#pragma once
#include <iostream>
#include <vector>
using namespace std;

class tablero
{
private:
    vector<vector<char>> matriz;
    char jugadorActual;
    char oponente;
    bool juegoTerminado;

public:
    tablero(char jugadorActualIngresado);
    
    bool getJuegoTerminado();
    void setJuegoTerminado(bool estado);
    char getCasilla(int fila, int columna);
    void setCasilla(int fila, int columna, char dato);
    int getSize();
    void imprimirTablero();
    int contarEspaciosVacios();
    void reiniciarTablero();
    int calcularPuntaje();
    bool tableroLleno();
    void cambiarJugador();
    char getJugadorActual();
    char getOponente();
    bool compararCon(tablero tableroAComparar);
};