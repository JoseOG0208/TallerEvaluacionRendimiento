/**************************************************************
Pontificia Universidad Javeriana
Nombre: Jose David Ontiveros
Fecha: 05/05/2025
Sistemas Operativos
Taller de Evaluación de Rendimiento
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "Biblioteca.h"

//punteros globales a las matrices A, B y C
double *mA, *mB, *mC;
//tamaño de la matriz
static double MEM_CHUNK[DATA_SIZE];
//mutex para sincronizacion de hilos
pthread_mutex_t MM_mutex;
//variables para medir el tiempo
struct timeval start, stop;

int main(int argc, char *argv[]) {
    //verificar el numero de argumentos ingresados
    if (argc < 3) {
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        return -1;    
    }

    //tamaño de la matriz y cantidad de hilos
    int SZ = atoi(argv[1]); 
    int n_threads = atoi(argv[2]); 

    //declaracion de los hilos y atributos de los hilos
    pthread_t p[n_threads];
    pthread_attr_t atrMM;

    //asignacion de memoria para las matrices A, B y C
    mA = MEM_CHUNK;
    mB = mA + SZ * SZ;
    mC = mB + SZ * SZ;

    //llenar las matrices A y B con valores iniciales y mostrar
    llenar_matriz(SZ);
    print_matrix(SZ, mA);
    print_matrix(SZ, mB);

    //inicializar el tiempo y configuraciones de los hilos
    inicial_tiempo();
    pthread_mutex_init(&MM_mutex, NULL);
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    //crear los hilos para la multiplicacion de matrices
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
        datos->idH = j;
        datos->nH = n_threads;
        datos->N = SZ;
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);
    }

    //esperar a que todos los hilos terminen
    for (int j = 0; j < n_threads; j++) {
        pthread_join(p[j], NULL);
    }

    //calcular y mostrar el tiempo final
    final_tiempo();
    
    //imprimir la matriz resultante
    print_matrix(SZ, mC);

    //liberar recursos
    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);
    pthread_exit(NULL);
}