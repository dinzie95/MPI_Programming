#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

// Creates an array of random numbers. Each number has a value from 0 - 1000
int *create_rand_nums(int num_elements) {
  int *rand_nums = (int *)malloc(sizeof(int) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = (rand() % 1000);
  }
  return rand_nums;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: avg num_elements_per_proc\n");
    exit(1);
  }

  int num_elements_per_proc = atoi(argv[1]);

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Create a random array of elements on all processes.
  srand(time(NULL)*world_rank);   // Seed the random number generator to get different results each time for each processor
  int *rand_nums = NULL;
  rand_nums = create_rand_nums(num_elements_per_proc);

  // Sum the numbers locally
  int local_sum = 0;
  int i;
  for (i = 0; i < num_elements_per_proc; i++) {
    local_sum += rand_nums[i];
  }

  // Print the random numbers on each process
  printf("Local sum for process %d - %d, avg = %d\n",
         world_rank, local_sum, local_sum / num_elements_per_proc);

  // Reduce all of the local sums into the global sum
  int global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
             MPI_COMM_WORLD);

  // Print the result
  if (world_rank == 0) {
    printf("Total sum = %d, avg = %d\n", global_sum,
           global_sum / (world_size * num_elements_per_proc));
  }

  // Clean up
  free(rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
