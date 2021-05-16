#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>


/* Function filling the array */
void fillArray(int n, int arr[n]){

    for(int i = 0; i < n; i++) {
        arr[i] = i+1;
    }

}

/* Function binarySearch */
void binarySearch (int n, int array[n], int key, int proc_id){

    int start = 0;
    int end = n - 1;

    if (key > array[start] && key < array[end]) {
        int root = 0;

        while(start <= end && array[root] != key ){

            root = (start + end) / 2;

            if (array[root] == key)
            {

                printf("Key %d found by process %d \n", key, proc_id);

            }
            else if (array[root] < key)
            {
                start = root + 1;
            }
            else
            {
                end = root -1;
            }
        
        }
    }

} 

/*Main Function*/ 
int main(int argc, char* argv[]) {

    int proc_id, total_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

/* Receiving the arguments from CLI */
    if (argc > 1) {

    int n, key;

    n = atoi(argv[1]);
    key = atoi(argv[2]);
/*--------------------------#%C0rs1C2lmp3-------*/

    int array[n];
    int blockSize = n /total_procs;
    int partialBlock[blockSize];

    if (proc_id == 0)
    {
        fillArray(n, array);
    }
    
    MPI_Scatter(
        array,
        blockSize,
        MPI_INT,
        partialBlock,
        blockSize,
        MPI_INT,
        0,
        MPI_COMM_WORLD);
    
    binarySearch(blockSize, partialBlock, key, proc_id);


/* Dividing the jobs among selected process 
    for(int i = proc_id * blockSize; (proc_id + 1) * blockSize; i++) {

        binarySearch(n, array, key, proc_id);

    }
*/
/*----------------------------------*/

    }

    return 0;

}

/*=======================================================

Program elaborated by 
Alfonso Valencia Sandoval, 
Roberto Antonio Velasco Munguía,
Gilberto Felipe Ramírez García
University of Colima
Faculty of Telematics
Parallel Programming

Cluster:
ssh curso11@148.228.4.17
#%C0rs1C2lmp3

=======================================================*/
