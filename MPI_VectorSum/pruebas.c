// ssh curso11@148.228.4.17
// #%C0rs1C2lmp3

// module load Compilers/Parallel-Studio-XE-2018
// mpiicc suma.c -o suma
// qsub mpi_run.sh
// qstat
// tail -f sumaVector.out

#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
    int this_proc, total_procs;
    int size_A = 10;
    int vector[size_A];

    for (int c = 0; c < size_A; c++) 
    {
        vector[c] = rand()%11;
        printf("%d ", vector[c]);
    }  

    /* Aqui comienza el paralelismo */

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_proc);

    int suma[total_procs];
    for (int x = 0; x < total_procs; x++)
    {
        suma[x] = 0;
    }

    MPI_Bcast(&suma, total_procs, MPI_INT, 0, MPI_COMM_WORLD); 

    int block_size = size_A / total_procs;
    clock_t tini, tfin, total_t; 

    tini = clock();
    for (int i = this_proc * block_size; i < (this_proc + 1) * block_size; i++)
    {
        suma[this_proc] += vector[i];
    }
    tfin = clock();

    total_t = (double)(tfin - tini) / CLOCKS_PER_SEC;

    MPI_Finalize();

    printf("\nTiempo total de ejecución:  %f segundos \n", total_t);

    for (int i = 0; i < total_procs; i++)
    {
        printf("La suma del procesador %d de %d procesasdores = %d \n", i, total_procs, suma[i]);
    } 

    return 0;
}


