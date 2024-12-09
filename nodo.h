#pragma once
#include "tablero.h"
#include <vector>

class nodo{
    private:
        vector<nodo*> hijos;
        tablero* tableroActual;
        int puntaje; 
        int altura;
        int alfa;
        int beta;
        bool esMax;
        pair<int,int> casillaJugadaActual;
    public:
        nodo(tablero* tableroActual, int altura, char jugadorActual, pair<int,int> casillaJugadaActualIngresada);
        vector<nodo*> getHijos();
        nodo* getHijo(int i);
        int getCantidadHijos();
        void agregarHijo(nodo* hijo);
        int getPuntaje();
        void setPuntaje(int puntajeIngresado);
        int getAltura();
        void setAltura(int alturaIngresada);

        

        int getAlfa();
        int getBeta();

        void setAlfa(int alfa);
        void setBeta(int beta);

        bool getEsMax();
        void setEsMax(char jugadorActual);

        pair<int,int> getCasillaJugadaActual();

        void buscarMin();
        void buscarMax();

        ~nodo();

        bool compararPuntaje(nodo* nodo);



};
