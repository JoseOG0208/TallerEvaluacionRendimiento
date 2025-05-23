/**************************************************************
Pontificia Universidad Javeriana
Nombre: Jose David Ontiveros
Fecha: 05/05/2025
Sistemas Operativos
Taller de Evaluación de Rendimiento
****************************************************************/
    
#include "Biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//funcion para llenar las matrices A y B con valores iniciales
void llenar_matriz(int SZ) { 
    srand48(time(NULL));
    for (int i = 0; i < SZ * SZ; i++) {
        mA[i] = 1.1 * i;
        mB[i] = 2.2 * i;
        mC[i] = 0;
    }    
}

//funcion para imprimir una matriz si su tamaño < 12
void print_matrix(int sz, double *matriz) {
    if (sz < 12) {
        for (int i = 0; i < sz * sz; i++) {
            if (i % sz == 0) printf("\n");
            printf(" %.3f ", matriz[i]);
        }    
        printf("\n>-------------------->\n");
    }
}

//funcion para inicializar el temporizador
void inicial_tiempo() {
    gettimeofday(&start, NULL);
}

//funcion para calcular y mostrar el tiempo transcurrido
void final_tiempo() {
    gettimeofday(&stop, NULL);
    stop.tv_sec -= start.tv_sec;
    printf("\n:-> %9.0f \n", (double) (stop.tv_sec * 1000000 + stop.tv_usec));
}

//funcion de multiplicación de matrices en paralelo
void *mult_thread(void *variables) {
    struct parametros *data = (struct parametros *)variables;
    
    int idH = data->idH;
    int nH = data->nH;
    int N = data->N;
    int ini = (N / nH) * idH;
    int fin = (N / nH) * (idH + 1);

    //multiplicacion realizada por el hilo
    for (int i = ini; i < fin; i++) {
        for (int j = 0; j < N; j++) {
            double *pA = mA + (i * N); 
            double *pB = mB + j;
            double sumaTemp = 0.0;
            for (int k = 0; k < N; k++, pA++, pB += N) {
                sumaTemp += (*pA * *pB);
            }
            mC[i * N + j] = sumaTemp;
        }
    }

    //proteccion con mutex para evitar condiciones de carrera
    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);
    pthread_exit(NULL);
}