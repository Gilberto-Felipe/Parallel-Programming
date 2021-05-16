#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stddef.h>
#include "mpi.h"

#define M 4
#define N 4
#define P 4

void print_results(char *prompt, int a[M][P]);

int main(int argc, char *argv[])
{
        int rank, size, sum = 0;
        int a[M][N];
        int b[N][P];
        int c[M][P];
        int aa[M], cc[M];

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == 0)
        {
                /* Generate random matrixes a & b */
                printf("--Matriz A %d x %d -- \n", M, N);
                for (int i = 0; i < M; i++)
                {
                        for (int j = 0; j < N; j++)
                        {
                                a[i][j] = rand() % 11;
                                printf("%d ", a[i][j]);
                        }
                        printf("\n");
                }

                printf("--Matriz B %d x %d -- \n", N, P);
                for (int i = 0; i < N; i++)
                {
                        for (int j = 0; j < P; j++)
                        {
                                b[i][j] = rand() % 11;
                                printf("%d ", b[i][j]);
                        }
                        printf("\n");
                }

                printf("\n");
        }

        //scatter rows of first matrix to different processes
        MPI_Scatter(a, P * size, MPI_INT, aa, P * size, MPI_INT, 0, MPI_COMM_WORLD);

        //broadcast second matrix to all processes
        MPI_Bcast(b, N * P, MPI_INT, 0, MPI_COMM_WORLD);

        //perform vector multiplication by all processes
        for (int i = 0; i < M; i++)
        {
                for (int j = 0; j < P; j++)
                {
                        sum += aa[j] * b[j][i];
                }
                cc[i] = sum;
                sum = 0;
        }

        MPI_Gather(cc, P * size, MPI_INT, c, P * size, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Finalize();

        if (rank == 0)
        {
                print_results("C = ", c);
        }

        return 0;
}

void print_results(char *prompt, int a[M][P])
{
        int i, j;

        printf("\n\n%s\n", prompt);
        for (i = 0; i < N; i++)
        {
                for (j = 0; j < N; j++)
                {
                        printf(" %d", a[i][j]);
                }
                printf("\n");
        }
        printf("\n\n");
}