#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>




/* funciones */
void fillMatrix(int matrix[M][N], int MAX);
void printMatrix(int matrix[M][N], int MAX);

int main(int argc, char *argv[])
{
	int rank, size;
	int MAX = atoi(argv[1]);
	int VECTOR__A[MAX], VECTOR__B[MAX];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{

		fillMatrix(VECTOR__A, MAX);
		fillMatrix(VECTOR__B, MAX);
		/* mensajes enviados */
		MPI_Send(VECTOR__A, MAX, MPI_INT, RECIBE, 2, MPI_COMM_WORLD);
		MPI_Send(VECTOR__B, MAX, MPI_INT, RECIBE, 3, MPI_COMM_WORLD);
	}
	else
	{
		if (rank == RECIBE)
		{
			/* codigo para el nodo que recibirá los vectores */
			MPI_Recv(VECTOR__A, MAX, MPI_INT, MASTER, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(VECTOR__B, MAX, MPI_INT, MASTER, 3, MPI_COMM_WORLD, &status);
			printf("Vector A\n");
			printMatrix(VECTOR__A, MAX);
			printf("VECTOR B\n");
			printMatrix(VECTOR__B, MAX);
			MPI_Send(VECTOR__A, MAX, MPI_INT, SUMA, 2, MPI_COMM_WORLD);
			MPI_Send(VECTOR__B, MAX, MPI_INT, SUMA, 3, MPI_COMM_WORLD);
		} 
		else 
		{
			if (rank == SUMA)
			{
				/* codigo para el nodo que sumará los vectores */
				MPI_Recv(VECTOR__A, MAX, MPI_INT, RECIBE, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(VECTOR__B, MAX, MPI_INT, RECIBE, 3, MPI_COMM_WORLD, &status);
				int VECTOR__RES[MAX];
				int i;
				for(i = 0; i < MAX; i++)
				{
					VECTOR__RES[i] = (VECTOR__A[i] + VECTOR__B[i]);
				}
				printf("VECTOR RESULTANTE\n");
				printMatrix(VECTOR__RES);
			}
		}
	}
	MPI_Finalize();
	return 0;
}

void fillMatrix(int matrix[][], int MAX)
{
	srand(time(NULL));
	for(int n = 0; n < MAX; n++)
	{
        for(int m = 0; m < MAX; m++)
        {
            matrix[n][m] = (rand()%10) + 1;
        }		
	}
}

void printMatrix(int matrix[][], int MAX)
{
	for(int i = 0; i < MAX; i++)
	{
        for(int j = 0; j < MAX; _IO_UNIFIED_JUMPTABLES++)
        {
            printf("%d\n", matrix[i][j]);
        }	
		
	}
}