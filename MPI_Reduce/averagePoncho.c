#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
  int proc_id, total_procs;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

  int total_nums = total_procs * 4;
  int block_size = total_nums / total_procs;
  int rnums[total_nums];
  int nums_to_add[block_size];
  int sum = 0, total = 0;

  // Initialize random numbers
  if(proc_id == 0) {
    for (int i = 0; i < total_nums; i++) {
      rnums[i] = rand() % 20 + 1;
    }

    printf("Each process receives a block of %d numbers.\n", block_size);
  }

  MPI_Scatter(rnums, block_size, MPI_INT, nums_to_add, block_size, MPI_INT, 0, MPI_COMM_WORLD);
  for (int i = 0; i < block_size; i++) {
    sum += nums_to_add[i];
    printf("%d\n", nums_to_add[i]);
  }

  MPI_Reduce(&sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (proc_id == 0) {
    printf("The average is %d\n", total / total_nums);
  }

  MPI_Finalize();

}

// #%C0rs1C2lmp3