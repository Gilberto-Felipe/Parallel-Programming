Clúster BUAP

ssh curso11@148.228.4.17
#%C0rs1C2lmp3


// PROGRAMA SUMAVECTOR.C

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
        vector[c] = rand()%1001;
        printf("%d ", vector[c]);
    }

    /* Aqui comienza el paralelismo */

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_proc);
    int sumas[total_procs];
    for (int x = 0; x < total_procs; x++)
    {
        sumas[x] = 0;
    }

    MPI_Bcast(&sumas, total_procs, MPI_INT, 0, MPI_COMM_WORLD);    
    int block_size = size_A / total_procs;
    clock_t tini, tfin; 
    tini = clock();

    for (int i = this_proc * block_size; i < (this_proc + 1) * block_size; i++)
    {
        sumas[this_proc] += vector[i];
    }

    tfin = clock();

    MPI_Finalize();

    printf(" \nTardé %f segundos \n", ((double)(tfin - tini) / CLOCKS_PER_SEC));


    for (int x = 0; x < total_procs; x++)
    {
        printf("elemento %d = %d \n", x, sumas[x]);
    }
}


