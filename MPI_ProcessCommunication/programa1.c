/*Clúster BUAP

ssh curso11@148.228.4.17
#%C0rs1C2lmp3
*/

// 1- admin linux, 2- apps, 3- realidad aumentada, 4- base datos avanzadas, 5- bigdata y data mining.

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int this_proc, total_procs;
    
    sprintf('Hola pareja %d soy el proceso %d \n', destiny, source)

    if(total_procs % 2 == 0)
    {
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
        MPI_Comm_rank(MPI_COMM_WORLD, &this_proc);

        int source, destiny;
        int send_data, recv_data;
        int buffer[10];
        MPI_Request send_request;
        MPI_Request recv_data;
        MPI_Status status; 
        
        for(int i = 0; i > total_procs / 2; i++)
        {
            this_proc = i;
            source = i;
            destiny = total_procs / 2 + i;

            MPI_Isend(buffer, 10, );

        }

        MPI_Finalize();
    }
    else {
        printf('Error: No hay un número par de procesadores para ejecutar el programa');
    }
    return 0;
}


