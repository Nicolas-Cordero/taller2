# TALLER 2 - ESTRUCTURA DE DATOS C1 - NICOLAS CORDERO

## DOCENTE: JOSE VEAS

Integrante:
1) Nicolás Gonzalo Cordero Varas - nicolas.cordero01@alumnos.ucn.cl - rut: 20.543.155-1

## instrucciones para ejecutar el programa:
0) tener el compilador mingw/g++ instalado
1) abrir una terminal y acceder a la ruta del proyecto
2) ejecutar la siguiente linea de comando para compilar:
g++ main.cpp -o a
3) ejectutar la siguiente linea de comando para ejecutar:
.\ejecutable.exe 

# explicacion sobre el algoritmo utilizado:
el algoritmo MiniMax con poda alfa-beta se utiliza en juegos de dos jugadores para evaluar el mejor movimiento posible. A continuación, se explica detalladamente el funcionamiento:

## Propósito del Algoritmo
-MiniMax-:
Encuentra el mejor movimiento para un jugador (MAX o MIN) asumiendo que el oponente jugará de forma óptima.
Recursivamente evalúa todos los posibles estados del juego para determinar el movimiento óptimo.

-Poda Alfa-Beta-:
Optimiza el MiniMax descartando ramas del árbol de decisiones que no pueden influir en el resultado final.
Utiliza dos límites:
Alfa: El mejor valor que el jugador MAX puede garantizar hasta ahora.
Beta: El mejor valor que el jugador MIN puede garantizar hasta ahora.

# Explicación del Algoritmo

Caso Base: Nodo Hoja
Si el nodo actual (raiz) no tiene hijos (raiz->getCantidadHijos() == 0), significa que es un estado terminal del juego.
Se retorna el nodo porque ya tiene asignado un puntaje, que representa el resultado del juego desde esa posición.

if(raiz->getCantidadHijos() == 0){
    return raiz;
}

# Inicialización de Alfa y Beta
Se extraen los valores actuales de alfa y beta del nodo raíz.
mejorValor es una variable auxiliar que guarda el mejor puntaje encontrado durante la evaluación.

int alfa = raiz->getAlfa();
int beta = raiz->getBeta();
int mejorValor;

# Evaluación de Hijos (MAX o MIN)

Se verifica si el nodo actual es un nodo MAX (turno del jugador X) o MIN (turno del jugador O).
## -Caso MAX (Jugador X-):
El objetivo es maximizar el puntaje.
Inicializa mejorValor con el menor valor posible: numeric_limits<int>::min().
Itera por cada hijo del nodo actual, llama recursivamente a miniMaxPodaAlfaBeta y actualiza:
mejorValor: El puntaje más alto encontrado hasta ahora.
alfa: El máximo entre el valor actual de alfa y mejorValor.
Si beta <= alfa, significa que ya no es necesario evaluar más hijos porque MIN nunca permitirá que MAX llegue a este estado (poda alfa-beta).

if(raiz->getEsMax()){
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

## -Caso MIN (Jugador O)-:
El objetivo es minimizar el puntaje.
Inicializa mejorValor con el mayor valor posible: numeric_limits<int>::max().
Itera por cada hijo del nodo actual, llama recursivamente a miniMaxPodaAlfaBeta y actualiza:
mejorValor: El puntaje más bajo encontrado hasta ahora.
beta: El mínimo entre el valor actual de beta y mejorValor.
Si beta <= alfa, se realiza la poda alfa-beta como en el caso MAX.

else{
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

## Retorno del Mejor Nodo

El nodo raíz se actualiza con el mejor puntaje encontrado y se retorna para continuar la evaluación en niveles superiores.

return raiz;

# Ejemplo Simplificado
suponiendo el siguiente arbol:

            (raiz)
           /     \
         (3)     (5)
        / | \   / | \
      (1)(3)(4)(5)(9)(2)

Al evaluar raiz como MAX:
Evalúa el primer hijo (3):
Evalúa sus hijos (1, 3, 4): toma el mayor (4).
Actualiza mejorValor a 4.
Evalúa el segundo hijo (5):
Evalúa sus hijos (5, 9, 2): toma el mayor (9).
Si alfa >= beta, se detiene la evaluación.
Este proceso reduce las evaluaciones innecesarias, optimizando el rendimiento.

![image alt]("link")

# ANÁLISIS DE COMPLEJIDAD DEL ALGORITMO:


El análisis de complejidad del algoritmo MiniMax con y sin poda alfa-beta se realiza considerando dos aspectos principales:

Factores relevantes:

b: Factor de ramificación del árbol (el número promedio de movimientos posibles en cada turno).
d: Profundidad máxima del árbol (el número de turnos hasta llegar a un estado terminal).
Evaluaciones necesarias:

Sin poda alfa-beta, el algoritmo evalúa todos los nodos del árbol.
Con poda alfa-beta, reduce la cantidad de nodos evaluados gracias a las podas.
1. Complejidad Sin Poda Alfa-Beta
En un árbol de decisión sin poda, el algoritmo explora todos los nodos posibles, lo que implica una complejidad:

O^(b^d)
Razón:

Cada nivel del árbol tiene hasta b nodos (factor de ramificación).
El árbol tiene d niveles (profundidad).
en el peor caso el numero total de nodos explorados es b^d aproximadamente

Problema:

Esta complejidad es exponencial, lo que hace que el algoritmo sea computacionalmente costoso para juegos con muchos movimientos posibles o gran profundidad.


2. Complejidad Con Poda Alfa-Beta
Con poda alfa-beta, el algoritmo elimina muchas ramas del árbol que no son necesarias para tomar decisiones óptimas. La cantidad de nodos explorados depende de:

El orden en que se exploran los nodos (si el orden es ideal, la poda es más eficiente).
En el mejor caso, el número de nodos evaluados se reduce casi a la mitad.
Complejidad en el mejor caso:
O^(b^(d/2))

Razón:
La poda permite evaluar solo la mitad del árbol, ya que se descartan muchas ramas a medida que α y 𝛽 se actualizan.

Complejidad en el peor caso:

O^(b^(d))
Razón:
Si el orden de exploración de los nodos es subóptimo (es decir, se evalúan primero las ramas menos favorables), la poda no logra reducir significativamente las evaluaciones.

Conclusión:
Con la poda alfa beta existe una ventaja real, ya que es especialmente efectiva cuando el orden de exploración de los nodos es cercano al óptimo. Por eso, técnicas adicionales como ordenar los movimientos antes de evaluarlos (ej., movimientos más prometedores primero) pueden potenciar su eficiencia.