#include <iostream>
#include "tablero.cpp"
#include "nodo.cpp"
#include <vector>
#include <limits>
using namespace std;

nodo* crearArbolEstadosTablero(nodo* raiz, bool esMaxIngresado, int contadorIngresado) {
    vector<pair<int,int>> indicesMatriz = {{0,0},{0,1},{0,2},
                                           {1,0},{1,1},{1,2},
                                           {2,0},{2,1},{2,2}};
    int contador = 0;
    char jugadorActual;
    char oponente;
    if (esMaxIngresado) {
        jugadorActual = 'X';
        oponente = 'O';
    } else {
        jugadorActual = 'O';
        oponente = 'X';
    }

    for (int juas = 0; juas < contadorIngresado; juas++) {
        int i = indicesMatriz[juas].first;
        int j = indicesMatriz[juas].second;

        tablero tableroAux = raiz->getTableroActual();
        tableroAux.setCasilla(i, j, jugadorActual);
        nodo* hijo = new nodo(&tableroAux, raiz->getAltura() + 1, oponente, {i, j});

        if (tableroAux.calcularPuntaje() == 10) {
            hijo->setPuntaje(10);
            raiz->agregarHijo(hijo);
        } else if (tableroAux.calcularPuntaje() == -10) {
            hijo->setPuntaje(-2);
            raiz->agregarHijo(hijo);
        } else if (tableroAux.tableroLleno()) {
            hijo->setPuntaje(-1);
            raiz->agregarHijo(hijo);
        } else {
            int copia = contadorIngresado - contador - 1; // Ajuste para evitar bucle infinito
            if (copia > 0) { // Asegurarse de que la recursión termine
                raiz->agregarHijo(crearArbolEstadosTablero(hijo, !esMaxIngresado, copia));
            }
        }
        contador++;
    }
    return raiz;
}




nodo* miniMaxPodaAlfaBeta(nodo* raiz){
    if(raiz->getCantidadHijos() == 0){
        return raiz;
    }
    int alfa = raiz->getAlfa();
    int beta = raiz->getBeta();
    int mejorValor;

    if(raiz->getEsMax()){
        // TURNO X, MAX
        mejorValor = numeric_limits<int>::min();
        for(nodo *hijo : raiz->getHijos()){
            
            hijo = miniMaxPodaAlfaBeta(hijo);
            mejorValor = max(mejorValor, hijo->getPuntaje());
            alfa = max(alfa, mejorValor);
            raiz->setPuntaje(mejorValor);
            if(beta <= alfa){

                break; // PODA ALFA BETA
            }
        }
    }
    else{
        // TURNO O, MIN
        mejorValor = numeric_limits<int>::max();
        for(nodo *hijo : raiz->getHijos()){

            hijo = miniMaxPodaAlfaBeta(hijo);
            mejorValor = min(mejorValor, hijo->getPuntaje());
            beta = min(beta, mejorValor);
            raiz->setPuntaje(mejorValor);
            if(beta <= alfa){
                break; // PODA ALFA BETA
            }

        }
    }
    return raiz;
    

}

nodo* encontrarMejorMovimiento(nodo* raiz){
    raiz->setAlfa(numeric_limits<int>::min());
    raiz->setAlfa(numeric_limits<int>::max());
    raiz = miniMaxPodaAlfaBeta(raiz);
    for(nodo* hijo : raiz->getHijos()){
        if(hijo->getPuntaje() == raiz->getPuntaje()){
            raiz = hijo;
            break;
        }
    }
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
        

        
        
    }
    return 0;
}

void pvia(){
    tablero* inicial = new tablero('X');
    cout << "ACA1!!" << endl;
    nodo* raiz = new nodo(inicial, 1, 'O', {-1,-1});
    raiz = crearArbolEstadosTablero(raiz, false, 9); 
    cout << "ACA2!!" << endl;
    nodo* actual = raiz;

    actual->getTableroActual().imprimirTablero();

    
    while(actual->getCantidadHijos() != 0){
        if(actual->getTableroActual().getJugadorActual() == 'X'){
        // TURNO HUMA
            tablero aux = actual->getTableroActual();

            ///INPUT HUMANO
            char columnaChar;
            int columna, fila;
            cout << "Jugador " << 'X' << " ingrese la COLUMNA (A, B o C): ";
            cin >> columnaChar;
            columna = conversorSimpleLetra(columnaChar);
            while (columna == -1)
            {
                cout << "Columna invalida, intente de nuevo" << endl;
                cout << "Jugador " << 'X' << " ingrese la COLUMNA (A, B o C): ";
                cin >> columnaChar;
                columna = conversorSimpleLetra(columnaChar);
            }
            cout << "Jugador " <<'X' << " ingrese la FILA (0, 1 o 2): ";
            cin >> fila;
            while (fila < 0 || fila > 2)
            {
                cout << "Fila invalida, intente de nuevo" << endl;
                cout << "Jugador " << 'X' << " ingrese la FILA (0, 1 o 2): ";
                cin >> fila;
            }

            cout <<"DEBUG 1" << endl;

            aux.setCasilla(fila, columna, 'X');
            cout <<"DEBUG 2" << endl;
            
            
            cout <<"DEBUG 3" << endl;

        cout <<"TERMINA TURNO HUMANO" << endl;
        actual->setEsMax(false);
        actual->getTableroActual().cambiarJugador();
        }
        
        else{
            actual->getTableroActual().imprimirTablero();    
            actual->setAlfa(numeric_limits<int>::min());
            actual->setBeta(numeric_limits<int>::max());
            actual = miniMaxPodaAlfaBeta(actual);
            for(nodo* hijo : actual->getHijos()){
                if(hijo->getPuntaje() == actual->getPuntaje()){
                    actual = hijo;
                    break;
                }
            }
        }
        
        
        cout << "jugador actual" <<actual->getTableroActual().getJugadorActual() << endl;
        cout <<"TERMINA TURNO IA" << endl;
    }
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
            try
            {
                pvia();
            }
            catch(const bad_alloc& e)
            {
                cout<<"Error de asignacion de memoria"<<endl;
            }
            

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