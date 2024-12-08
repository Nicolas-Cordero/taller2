#include <iostream>
#include <vector>
using namespace std;

class tablero{
    private:
        vector<vector<char>> matriz;
        char jugadorActual;
    public:
        tablero(){
            matriz = vector<vector<char>>(3, vector<char>(3, ' '));
            jugadorActual = 'X';
        }
        void imprimirTablero(){ /// funcion 1, imprimir tablero
            cout << "    A   B   C" << endl;
            cout << "  +---+---+---+" << endl;
            for (int i = 0; i < 3; i++){
                cout << i << " |"<< " ";
                for (int j = 0; j < 3; j++){
                    cout << matriz[i][j];
                    cout << " | ";
                    
                }
                cout << endl;
                cout << "  +---+---+---+" << endl;
            }
        }
        bool hacerMovimiento(int fila, int columna){ /// funcion 2, hacer movimiento
            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && matriz[fila][columna] == ' '){
                matriz[fila][columna] = jugadorActual;
                return true;
            }
            return false;
        }
        bool hayGanador(){ /// funcion 3, hay ganador
            for (int i = 0; i < 3; ++i){
                // verificamos filas y columnas
                if ((matriz[i][0] == jugadorActual && matriz[i][1] == jugadorActual && matriz[i][2] == jugadorActual)
                 || (matriz[0][i] == jugadorActual && matriz[1][i] == jugadorActual && matriz[2][i] == jugadorActual)){
                    return true;
                }
                // verificamos diagonales
                return ((matriz[0][0] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][2] == jugadorActual)
                 || (matriz[0][2] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][0] == jugadorActual));
                
            }
            
        }
        bool tableroLleno(){ /// funcion 4, tablero lleno
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (matriz[i][j] == ' '){
                        return false;
                    }
                }
            }
            return true;
        }
        void cambiarJugador(){ /// funcion 5, cambiar jugador
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
        }
        char getJugadorActual(){ /// funcion 6, obtener jugador actual
            return jugadorActual;
        }
        void reiniciarTablero(){ /// funcion 7, reiniciar tablero
            matriz = vector<vector<char>>(3, vector<char>(3, ' '));
            jugadorActual = 'X';
        }
        void setMovimiento(int fila, int columna, char jugador){ /// funcion 8, set movimiento
            matriz[fila][columna] = jugador;
        }

};