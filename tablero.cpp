#include <iostream>
#include <vector>
using namespace std;

class tablero{
    private:
        vector<vector<char>> matriz;
        char jugadorActual;
        char oponente; 
        bool juegoTerminado;
    public:
        tablero(){ // constructor
            matriz = vector<vector<char>>(3, vector<char>(3, ' '));
            jugadorActual = 'X';
            juegoTerminado = false;
        }
        bool gerJuegoTerminado(){ // get juego terminado
            return juegoTerminado;
        }
        bool setJuegoTerminado(bool estado){ // set juego terminado
            juegoTerminado = estado;
        }     
        char getDato(int fila, int columna){ // get dato dada posicion
            return matriz[fila][columna];
        }
        int getSize(){ // get size
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
        bool hacerMovimiento(int fila, int columna){ /// funcion 2, hacer movimiento
        // dada posicion se inserta el jugador actual
            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && matriz[fila][columna] == ' '){
                matriz[fila][columna] = jugadorActual;
                return true;
            }
            return false;
        }
        // dada posicion se inserta el char ingresado
        bool hacerMovimientoForzado(int fila, int columna, char forzado){ /// funcion 2, hacer movimiento
            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && matriz[fila][columna] == ' '){
                matriz[fila][columna] = forzado;
                return true;
            }
            return false;
        }

        int contarEspaciosVacios (){ /// funcion 2.1, contar espacios vacios
            int contador = 0;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (matriz[i][j] == ' '){
                        contador++;
                    }
                }
            }
            return contador;
        }

        int calcularCostoTablero(){
            // Horizontal
            for (int i = 0; i < 3; ++i){
                if(matriz[i][0] == matriz[i][1] && matriz[i][1] == matriz[i][2] && matriz[i][0] != ' '){
                    if(matriz[i][0] == 'X'){
                        return 10;
                        //return (contarEspaciosVacios()+1)  ;
                    }
                    else if (matriz[i][0] == 'O'){
                        return -10;
                        //return -(contarEspaciosVacios()+1);
                        
                    }
                
            }

            // vertical 
            for (int j = 0; j < 3; j++){
                if (matriz[0][j] == matriz[1][j] && matriz[1][j]  == matriz[2][j] && matriz[0][j] != ' '){
                    if(matriz[0][j] == 'X'){
                        return 10;
                        //return (contarEspaciosVacios()+1);
                    }
                    else if (matriz[0][j] == 'O'){
                        return -10;
                        //return -(contarEspaciosVacios()+1);
                        
                    }
                }
            }
        
            

            // Diagonal
            if(matriz[0][0] == matriz[1][1] &&  matriz[1][1] == matriz[2][2] && matriz[0][0] != ' '){
                if(matriz[0][0] == 'X'){
                    return 10;
                    //return (contarEspaciosVacios()+1);
                }
                else if (matriz[0][0] == 'O'){
                    return -10;
                    //return -(contarEspaciosVacios()+1);
                    
                }
            }
            if (matriz[0][2] ==  matriz[1][1] && matriz[1][1] == matriz[2][0] && matriz[0][2] != ' '){
                 if(matriz[0][0] == 'X'){
                    return 10;
                    //return (contarEspaciosVacios()+1);
                }
                else if (matriz[0][0] == 'O'){
                    return -10;
                    //return -(contarEspaciosVacios()+1);
                    
                }
            }
                // casilleros vacios
                return 0;
            }
        }

        char hayGanador(){ /// funcion 3, hay ganador
            for (int i = 0; i < 3; ++i){
                // horizontales
                if ((matriz[i][0] == jugadorActual && matriz[i][1] == jugadorActual && matriz[i][2] == jugadorActual) ||
                (matriz[0][i] == jugadorActual && matriz[1][i] == jugadorActual && matriz[2][i] == jugadorActual)){
                    juegoTerminado = true;
                    return jugadorActual;
                }
                // verticales
                else if ((matriz[0][0] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][2] == jugadorActual) ||
                (matriz[0][2] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][0] == jugadorActual)){
                    juegoTerminado  = true;
                    return jugadorActual;
                }
            }
            // diagonales
            if ((matriz[0][0] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][2] == jugadorActual) ||
                (matriz[0][2] == jugadorActual && matriz[1][1] == jugadorActual && matriz[2][0] == jugadorActual)) {
                juegoTerminado = true;  
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
            juegoTerminado = true;
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