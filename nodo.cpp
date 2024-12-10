#include "nodo.hpp"
#include "tablero.hpp"
#include <vector>

nodo::nodo(tablero* t, int altura, char jugadorActualIngresado, pair<int,int> casillaJugadaActualIngresada){
    hijos = vector<nodo*>();
    tableroActual = t;
    if (jugadorActualIngresado == 'X'){
        esMax = true;
    }
    else{
        esMax = false;
    }
    alfa = -1000;
    beta = 1000;

    puntaje = t->calcularPuntaje();

    casillaJugadaActual = casillaJugadaActualIngresada;
}

vector<nodo*> nodo::getHijos(){
    return hijos;
}
nodo* nodo::getHijo(int i){
    return hijos[i];
}
int nodo::getCantidadHijos(){
    return hijos.size();
}
void nodo::agregarHijo(nodo* hijo){
    hijos.push_back(hijo);
}
int nodo::getPuntaje(){
    return puntaje;
}
void nodo::setPuntaje(int puntajeIngresado){
    puntaje = puntajeIngresado;
}
int nodo::getAltura(){
    return altura;
}
void nodo::setAltura(int alturaIngresada){
    altura = alturaIngresada;
}

bool nodo::compararPuntaje(nodo* nodo){
    tableroActual->compararCon(*nodo->tableroActual);
}

int nodo::getAlfa(){
    return alfa;
}
int nodo::getBeta(){
    return beta;
}

void nodo::setAlfa(int alfaIngresado){
    alfa = alfaIngresado;
}

void nodo::setBeta (int betaIngresado){
    beta = betaIngresado;
}

bool nodo::getEsMax(){
    return esMax;
}
void nodo::setEsMax(char jugadorActual){
    if (jugadorActual == 'X'){
        esMax = true;
        tableroActual->cambiarJugador();
    }
    else{
        esMax = false;
        tableroActual->cambiarJugador();
    }
}  

tablero nodo::getTableroActual(){
    return *tableroActual;
}

nodo::~nodo() {
    for (auto hijo : hijos) {
        delete hijo;
    }
}
