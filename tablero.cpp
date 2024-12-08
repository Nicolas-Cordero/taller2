#include <iostream>
#include <vector>
using namespace std;

class tablero{
    private:
        vector<vector<char>> matriz;
        char jugadorActual;
        char oponente; 
    public:
        tablero(){
            matriz = vector<vector<char>>(3, vector<char>(3, ' '));
            jugadorActual = 'X';
        }
        char getDato(int fila, int columna){
            return matriz[fila][columna];
        }
        int getSize(){
            return matriz.size();
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
        bool hacerMovimiento(int fila, int columna, char jugadorForzado){ /// funcion 2, hacer movimiento
            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && matriz[fila][columna] == ' '){
                if (jugadorForzado != ' '){
                    matriz[fila][columna] = jugadorForzado;
                    return true;
                }
                matriz[fila][columna] = jugadorActual;
                return true;
            }
            return false;
        }
        char hayGanador(){ /// funcion 3, hay ganador
            for (int i = 0; i < 3; ++i){
              
                if ((matriz[i][0] == jugadorActual && matriz[i][1] == jugadorActual && matriz[i][2] == jugadorActual) ||
                (matriz[0][i] == jugadorActual && matriz[1][i] == jugadorActual && matriz[2][i] == jugadorActual)){
                    return jugadorActual;
                }

                else if ((matriz[0][0] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][2] == jugadorActual) ||
                (matriz[0][2] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][0] == jugadorActual)){
                    return jugadorActual;
                }
            }
            if ((matriz[0][0] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][2] == jugadorActual) ||
                (matriz[0][2] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][0] == jugadorActual)) {
                return jugadorActual;
            }
            return ' ';
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
            if (jugadorActual == 'X'){
                oponente = 'O';
            }
            else{
                oponente = 'X';
            }
        }
        char getJugadorActual(){ /// funcion 6, obtener jugador actual
            return jugadorActual;
        }
        char getOponente(){ /// funcion 6.1, obtener oponente
            return oponente;
        }
        void reiniciarTablero(){ /// funcion 7, reiniciar tablero
            matriz = vector<vector<char>>(3, vector<char>(3, ' '));
            jugadorActual = 'X';
        }
        void setMovimiento(int fila, int columna, char jugador){ /// funcion 8, set movimiento
            matriz[fila][columna] = jugador;
        }

};