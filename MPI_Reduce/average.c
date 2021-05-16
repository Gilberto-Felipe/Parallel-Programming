// https://stackoverflow.com/questions/41575243/matrix-multiplication-using-mpi-scatter-and-mpi-gather

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/* function to generate and return random numbers */
int * generateData(int n) {

    int vector[n]; // array of 8 elements

    /* cycle to generate the random array */ 
    for (int i = 0; i < n; i++) {
        vector[i] = rand()%10 + 1;
    }
    
    /* cycle to print the array */ 
    for (int i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }

    return vector;
}

int main(int argc, char *argv[])
{
    int proc_id, total_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    /* Variables */ 
    int n = total_procs * 4; // total number of elements of the random vector
    int block = n / total_procs; // blockSize to scatter
    int numsToAdd[block];// partial array of each process
    int sum = 0, total = 0;
    int *p; // a pointer to an int

    if (proc_id = 0) {
        int n = 8; // vectorSize
        // int total_procs = 2; // total process
        p = generateData(n); 

        /*printing the number of elements for processes */
        printf("\nEach process receives a block of %d numbers.\n", block); // print the message
    }
    
    MPI_Scatter(p, block, MPI_INT, numsToAdd, block, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < block; i++) {
        sum += numsToAdd[i];
        printf("%d\n", numsToAdd[i]);
    }

    MPI_Reduce(&sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (proc_id == 0) {
        printf("The average is %d\n", total / n);
    }
    
    MPI_Finalize();

    return 0;
}
