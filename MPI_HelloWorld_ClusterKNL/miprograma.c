#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int this_proc, total_procs;

    /* Aqui comienza el paralelismo */

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);

    MPI_Comm_rank(MPI_COMM_WORLD, &this_proc);

    printf("Hola mundo! Soy el proceso nro. %d de un total de %d procesos.\n", this_proc, total_procs);

    MPI_Finalize();
}