#include "tablero.cpp"
#include <iostream>
#include <limits>
using namespace std;

int minimax2(tablero &t, const int &profundidad, const bool &max, int alfa, int beta)
{
    int puntaje = t.calcularCostoTablero();
    if (puntaje == 10 || puntaje == -10 || t.tableroLleno())
    {
        return puntaje;
    }

    if (max)
    {
        int maxEvaluar = -10000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (t.getDato(i, j) == ' ')
                {
                    // populamos el tablero con el jugador actual
                    t.hacerMovimientoForzado(i, j, 'X');
                    cout << "Despues de hacer movimiento en (" << i << " " << j << "): " << endl;
                    t.imprimirTablero();

                    // llamada recursiva
                    maxEvaluar = std::max(maxEvaluar, minimax2(t, profundidad + 1, false, alfa, beta));


                    t.setMovimiento(i, j, ' ');
                    cout << "Despues de deshacer movimiento en (" << i << " " << j << "): " << endl;
                    t.imprimirTablero();

                    t.setJuegoTerminado(false);
                    // poda alfa beta
                    alfa = std::max(alfa,maxEvaluar);
                    if (alfa >= beta)
                    {
                        return maxEvaluar;
                    }   
                }
            }
        }
        return maxEvaluar;
    }
    else
    {
        int minEvaluar = 10000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (t.getDato(i, j) == ' ')
                {
                    // populamos el tablero con el jugador actual
                    t.hacerMovimientoForzado(i, j, 'O');
                    cout << "Despues de hacer movimiento en (" << i << " " << j << "): " << endl;
                    t.imprimirTablero();

                    minEvaluar = min(minEvaluar, minimax2(t, profundidad + 1, true, alfa, beta));

                    t.setMovimiento(i, j, ' ');
                    cout << "Despues de deshacer movimiento en (" << i << " " << j << "): " << endl;
                    t.imprimirTablero();

                    t.setJuegoTerminado(false);

                    // poda alfa beta
                    beta = std::min(beta,minEvaluar);

                    if(beta <= alfa){
                        return minEvaluar;
                    }
                }
            }
        }
        return minEvaluar;
    }
}

int *obtenerMejorMovimiento2(tablero t)
{
    int minMaxEvaluar = t.getJugadorActual() == 'X' ? -10000 : 10000;
    int *mejorMovimiento = new int[2];
    // loop en todos los hijos desde la posicion actual
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (t.getDato(i, j) == ' ')
            {
                // hacemos el movimiento actual
                t.setMovimiento(i, j, t.getJugadorActual() == 'X' ? 'X' : 'O');
                bool maxOrMin = t.getJugadorActual() == 'X' ? true : false;

                // evaluacion del movimiento con minimax
                int evaluar = minimax2(t, 0, maxOrMin, -10000, 10000);

                // deshacemos el movimiento
                t.setMovimiento(i, j, ' ');
                t.setJuegoTerminado(false);

                // obtenemos la maxima evaluacoin si el jugador es X
                if (t.getJugadorActual() == 'X')
                {
                    if (evaluar > minMaxEvaluar)
                    {
                        mejorMovimiento[0] = j;
                        mejorMovimiento[1] = i;

                        minMaxEvaluar = evaluar;
                    }
                }
                // obtenemos la minima evaluacion si el jugador es O
                else
                {
                    if (evaluar < minMaxEvaluar)
                    {
                        mejorMovimiento[0] = j;
                        mejorMovimiento[1] = i;
                        minMaxEvaluar = evaluar;
                    }
                }
            }
        }
    }
    if (t.getDato(mejorMovimiento[1], mejorMovimiento[0]) != ' ')
    {
        cout << "Error: movimiento inválido generado por la IA" << endl;
        return nullptr;
    }

    mejorMovimiento[2] = '\0';
    return mejorMovimiento;
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

int pvia()
{
    tablero t;
    t.imprimirTablero();
    int fila, columna;
    char columnaChar;
    while (true)
    {
        // Jugador
        cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
        cin >> columnaChar;
        columna = conversorSimpleLetra(columnaChar);
        while (columna == -1)
        {
            cout << "Columna invalida, intente de nuevo" << endl;
            cout << "Jugador " << t.getJugadorActual() << " ingrese la COLUMNA (A, B o C): ";
            cin >> columnaChar;
        }
        cout << "Jugador " << t.getJugadorActual() << " ingrese la FILA (0, 1 o 2): ";
        cin >> fila;

        if (t.hacerMovimiento(fila, columna))
        {
            t.imprimirTablero();
            if (t.hayGanador() != ' ')
            {
                cout << "Jugador " << t.getJugadorActual() << " ha ganado!" << endl;
                break;
            }
            if (t.tableroLleno())
            {
                cout << "Empate!" << endl;
                break;
            }
            t.cambiarJugador();
            /// IA
            cout << "-*--*-Es el turno de la IA-*--*- " << endl;
            int *mejorMovimiento = obtenerMejorMovimiento2(t);
            cout << "La IA ha seleccionado la casilla: " << mejorMovimiento[0] << "+" << mejorMovimiento[1] << endl;
            if (mejorMovimiento != nullptr && t.hacerMovimiento(mejorMovimiento[1], mejorMovimiento[0]))
            {
                t.imprimirTablero();
                if (t.hayGanador() != ' ')
                {
                    cout << "Jugador " << t.getJugadorActual() << " ha ganado!" << endl;
                    break;
                }
                if (t.tableroLleno())
                {
                    cout << "Empate!" << endl;
                    break;
                }
                t.cambiarJugador();
            }
            else
            {
                cout << "Movimiento invalido generado por la IA, intente de nuevo" << endl;
            }
        }
        else
        {
            cout << "Movimiento invalido, intente de nuevo" << endl;
        }
    }
    return 0;
}

int pvp()
{
    tablero t;
    t.imprimirTablero();
    int fila, columna;
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
        }
        cout << "Jugador " << t.getJugadorActual() << " ingrese la FILA (0, 1 o 2): ";
        cin >> fila;

        if (t.hacerMovimiento(fila, columna))
        {
            t.imprimirTablero();
            if (t.hayGanador() != ' ')
            {
                cout << "Jugador " << t.getJugadorActual() << " ha ganado!" << endl;
                break;
            }
            if (t.tableroLleno())
            {
                cout << "Empate!" << endl;
                break;
            }
            t.cambiarJugador();
        }
        else
        {
            cout << "Movimiento invalido, intente de nuevo" << endl;
        }
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