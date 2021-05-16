#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int main(int argc, char *argv[])
{

    /*=======================================
    VARIABLES DE ENTRADA NO PARALELIZABLES
    ========================================*/

    int this_proc, total_procs;
    /* 
    *this_proc recibe el id de procesador que está trabajando. 
    *total_procs recibe el número total de procesadores que van a trabajar.
    */

    int size_A = 10;
    //* Tamaño del vector

    int vector[size_A];
    //* inicializar un vector tamaño size_A

    /* --------------- GENERAR NÚMEROS PSEUDO ALEATORIOS ---------------*/

    for (int c = 0; c < size_A; c++) 
    {
        vector[c] = rand()%1001;
        printf("%d ", vector[c]);
    }
    /*--------------- fin generar números pseudo aleatorios ---------------*/

    /*==================== FIN VARIABLES DE ENTRADA ====================*/


    /*=======================================
    INICIO DEL PARALELISMO
    ========================================*/

    /* --------------- INVOCAR FUNCIONES MPI PARA INICIALIZAR PARALELISMO ---------------*/

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_proc);

    /* --------------- fin INVOCAR FUNCIONES MPI PARA INICIALIZAR PARALELISMO ---------------*/


    /* --------------- INICIALIZAR VECTOR SUMA EN 0 ---------------*/
    
    //* VARIABLE VECTOR SUMA
    int suma[total_procs];

    for (int x = 0; x < total_procs; x++)
    {
        suma[x] = 0;
    }

    /* --------------- fin INICIALIZAR VECTOR SUMA EN 0 ---------------*/


    // *INVOCAR FUNCIÓN DE BROADCAST DE MPI
    MPI_Bcast(&suma, total_procs, MPI_INT, 0, MPI_COMM_WORLD);  


    /* --------------- CADA PROCESADOR SUMA SU BLOQUE CORRESPONDIENTE ---------------*/

    //* VARIABLE DE TAMANIO DEL BLOQUE
    int block_size = size_A / total_procs;

    //* VARIABLE CON TIPO DE DATO PARA CAPTURAR TIEMPO DEL SISTEMA
    struct timeval stop, start; 
    
    //* FUNCIÓN OBTENER FECHA INICIO
    gettimeofday(&start, NULL);

    // * CADA PROCESADOR OBTIENE LA SUMA DE SU BLOQUE
    for (int i = this_proc * block_size; i < (this_proc + 1) * block_size; i++)
    {
        suma[this_proc] += vector[i];
    }

    // * FUNCIÓN OBTENER FECHA DE FIN
    gettimeofday(&stop, NULL);

    /* --------------- fin CADA PROCESADOR SUMA SU BLOQUE CORRESPONDIENTE ---------------*/

    // * FINALIZAR COMUNICACIÓN MPI
    MPI_Finalize();

    /*==================== FIN PARALELISMO ====================*/


    /*=======================================
    SALIDAS DEL PROGRAMA
    ========================================*/

    printf("Tardé %lu \n", stop.tv_usec - start.tv_usec);
    printf("Duración en MS %'.3f \n", (double) (stop.tv_sec - start.tv_sec) * 1000 + (double) (stop.tv_usec - start.tv_usec) / 1000);

    for (int x = 0; x < total_procs; x++)
    {
        printf("Posición %d = %d \n", x, suma[x]);
    }

    /*==================== FIN DEL PROGRAMA ====================*/
}

