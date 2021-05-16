#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int vector1[10], 
        vector2[10];
    int i, j, c, a, b;
    int nprocs = 2,
        proc_i = 0,
        suma = 0;

    printf("Vector1 aleatorio \n");

    srand (time(NULL));
    for (i=0; i<10; i++) 
    {
        vector1[i] = rand()%10;
        printf("%d ", vector1[i]);
    }

    for (proc_i; proc_i < nprocs; proc_i++)
    {
        for (c = proc_i * (10 / nprocs); c < 10 / nprocs * (proc_i + 1); c++)
            {
                suma += vector1[c];
            }
    }
    
    printf("Imprime la suma %d ", suma);

    return 0;
}
