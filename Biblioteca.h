#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <pthread.h>
#include <sys/time.h>

//tamaño del bloque de memoria para las matrices
#define DATA_SIZE (1024 * 1024 * 64 * 3)

//rstructura para los parametros de cada hilo
struct parametros {
    int nH;   // Número de hilos
    int idH;  // Identificador del hilo
    int N;    // Tamaño de la matriz
};

//declaracion de variables globales
extern pthread_mutex_t MM_mutex;
extern double *mA, *mB, *mC;
extern struct timeval start, stop;

//declaracion de funciones
void llenar_matriz(int SZ);
void print_matrix(int sz, double *matriz);
void inicial_tiempo();
void final_tiempo();
void *mult_thread(void *variables);

#endif