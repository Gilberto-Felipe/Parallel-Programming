#include <stdio.h>
#include <string.h>
#include <mpi.h>

int findTarget(int id, int total) {
  int half = total / 2;
  if (id < half)
    return id + half;
  else
    return id - half;
}

int main(int argc, char* argv[]) {
  int proc_id, total_procs;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

  if (total_procs % 2 == 0) {
    int target_proc = findTarget(proc_id, total_procs);
    char outgoing_message[31];
    char incoming_message[31];
    // Writing the message
    snprintf(outgoing_message, 31, "Hola pareja %d soy el proceso %d\n", target_proc, proc_id);

    // Sending message
    MPI_Send(&outgoing_message, 31, MPI_CHAR, target_proc, 0, MPI_COMM_WORLD);

    // Receiving message
    MPI_Status status;
    MPI_Recv(&incoming_message, 31, MPI_CHAR, target_proc, 0, MPI_COMM_WORLD, &status);

    printf("\nRecibe proceso %d:\n%s\n", proc_id, incoming_message);
  } else if (proc_id == 0) {
    printf("El total de procesos no es par...\n");
  }

  MPI_Finalize();

  return 0;
}

