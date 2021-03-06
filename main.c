/* 
 * @file main.c
 * @author Manuel Alférez Ruiz
 * @date 12 de mayo de 2018, 10:18
 * @note Problema 11
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * ENUNCIADO DEL PROBLEMA: 
 * Un fontanero necesita hacer n reparaciones urgentes, y sabe de antemano el 
 * tiempo que le va a llevar cada una de ellas: en la tarea i-ésima tardará t
 * minutos. Como en su empresa le pagan dependiendo de la satisfacción del cliente,
 * necesita decidir el orden en el que atenderá los avisos para minimizar el 
 * tiempo de espera de los clientes.
 * 
 * En otras palabras, si llamamos Ei a lo que espera el cliente i-ésimo hasta
 * ver reparada su avería por completo, necesita minimizar la expresión:
 * E(n)= Sumatorio (Ei)
 * 
 * Diseñar un algoritmo voraz que resuelva el problema y probar su validez, bien 
 * demostración formal o con un contraejemplo que la refute. 
 */

/**
 * SOLUCIÓN FORMAL:
 * La planificación óptima de reparaciones se da cuando se realizan las reparaciones
 * en orden creciente de tiempos. Prueba formal de ello es lo que sigue: supongamos
 * 4 tiempos 'a','b','c' y 'd'. La primera reparación termina en el minuto a, la
 * segunda en la a+b, etc. El tiempo promedio de finalización de todas las repaciones
 * es (4a+3b+2c+d)/4. Es evidente que 'a' contribuye más al promedio, por lo que 
 * debe ser la más corta, b la siguiente y así sucesivamente.
 */

/**
 * @brief Función de selección: Selecciona la reparación que lleva menos tiempo
 * entre las disponibles 
 * 
 * @param reparaciones Vector de reparaciones
 * @param n Número de reparaciones
 * @return Devuelve la posición con la reparación más óptima
 */
int seleccion(int reparaciones[], int n) {
    int mejorOpcion = 0; //Mejor repación que realizar
    for (int i = 1; i < n; i++) {
        if (reparaciones[i] < reparaciones[mejorOpcion]) mejorOpcion = i;
    }
    return mejorOpcion;
} //seleccion

/**
 * @brief Elimina una posición de un vector
 * 
 * @param v Vector
 * @param pos Posición a eliminar
 * @param n Tamaño del Vector
 */
void eliminar(int v[], int pos, int n) {
    v[pos] = v[n - 1];
} //eliminar

/**
 * @brief Nos informa si es factible añadir un elemento a la solución
 * 
 * @param vector Vector 
 * @param n El tamaño del vector
 * @return Devuelve 1 si es factible añadir otro elemento o 0 en caso contrario
 */
int factible(int v[], int n) {
    if (v[n - 1] != 0) return 0;
    else return 1;
} //factible

/**
 * @brief Función voraz
 * 
 * @param reparaciones Reparaciones urgentes
 * @param n Número de reparaciones
 * @return Devuelve un vector solución con la planificación que hay que realizar
 * en cada aviso
 */
int* algoritmoVoraz(int reparaciones[], int n) {
    int* S = malloc(n * sizeof (int)); //S es el conjunto de la solución
    //Inicializamos
    for (int i = 0; i < n; i++) S[i] = 0;
    //Variables
    int tam_S = 0, pos, ele, n_restantes = n;
    while (tam_S != n && n_restantes != 0) {
        pos = seleccion(reparaciones, n_restantes);
        ele = reparaciones[pos];
        eliminar(reparaciones, pos, n_restantes);
        n_restantes--;
        if (factible(S, n)) S[tam_S++] = ele;
    }
    return S;
} //algoritmoVoraz

/*
 * @brief Función principal: Ejemplo del problema. Muestra la planificación
 * de una serie de reparaciones por pantalla y la media en minutos de la espera 
 * media de los clientes
 * 
 * @param argc Número de parámetros por línea de ordenes
 * @param argv Parámetros por líneas de órdenes
 */
int main(int argc, char** argv) {

    //Vector de reparaciones urgentes
    int trabajos[] = {52, 1, 2, 6, 9, 8, 5, 45, 1, 4, 5, 33, 1, 25, 26, 78, 4, 12};
    int num_trabajos = 18;

    int* solucion = algoritmoVoraz(trabajos, num_trabajos);
    int media = 0;
    
    printf("Ordenación de reparaciones: ");
    for (int i = 0; i < num_trabajos; i++) {
        printf(" | %d", solucion[i]);
        media += solucion[i]*(i + 1); //Sumamos el tiempo de espera
    }

    printf("\nEspera media (en minutos): %d", media / 18);

    return (EXIT_SUCCESS);
} //main