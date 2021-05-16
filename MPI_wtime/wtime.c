#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

    int proc_id, total_procs;
    double starttime, endtime, globaltime;

    MPI_Init(&argc, &argv);

    starttime = MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    if (argc > 1)
    {

        int m, n, p;

        m = atoi(argv[1]);
        n = atoi(argv[2]);
        p = atoi(argv[3]);

        if (m >= total_procs && m % total_procs == 0)
        {
            int block_size = m / total_procs;
            int mA[m][n], mB[n][p], mC[m][p], pA[block_size][n], pC[block_size][p];

            if (proc_id == 0)
            {
                // Initialize the matrixes
                Generate_Matrix(n, m, mA);
                Generate_Matrix(p, n, mB);
            }

            // Broadcasting data and scattering blocks
            MPI_Scatter(&mA, n * block_size, MPI_INT, &pA, n * block_size, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(&mB, p * n, MPI_INT, 0, MPI_COMM_WORLD);

            // Performing multiplications
            Multiply_Matrices(block_size, n, p, pA, mB, pC);

            // Collecting results
            MPI_Gather(&pC, block_size * p, MPI_INT, &mC, block_size * p, MPI_INT, 0, MPI_COMM_WORLD);

            /* Printing results
            if (proc_id == 0)
            {
                printf("Printing A\n");
                Print_Matrix(m, n, mA);

                printf("Printing B\n");
                Print_Matrix(n, p, mB);

                printf("Printing C\n");
                Print_Matrix(m, p, mC);
            }*/
        }
        else if (proc_id == 0)
        {
            printf("Can't execute program: More processes than columns of A or there is no precise block size!\n");
        }
    }
    else if (proc_id == 0)
    {
        printf("Program usage: matrix-multiply <m> <n> <p>\n");
    }

    endtime = MPI_Wtime();

    printf("Process %d took %f seconds\n", proc_id, endtime - starttime);

    for (int i = 0; i < total_procs -1; i++) {
        globaltime += endtime - starttime;
    }

    MPI_Finalize();

    return 0;
}

void Generate_Matrix(int columns, int rows, int outM[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            outM[i][j] = (rand() % 15) + 1;
        }
    }

    return;
}

void Multiply_Matrices(int m, int n, int p, int mA[m][n], int mB[n][p], int outM[m][p])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            outM[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                outM[i][j] += mA[i][k] * mB[k][j];
            }
        }
    }
    return;
}

void Print_Matrix(int rows, int columns, int matrix[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}