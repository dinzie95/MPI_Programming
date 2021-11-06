#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char** argv) {
    
    int gsize,*sendarray; 
    int root, myrank, *receivebuffer;

    int count = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if ( myrank == 0) {
        MPI_Comm_size( MPI_COMM_WORLD, &gsize);
        receivebuffer = (int *)malloc(gsize*count*sizeof(int));
    }

    // random generator
    srand(time(NULL));

    // assign random values to sendarray from (1-100)
    sendarray = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        sendarray[i] = (rand() % 100);
    }

    MPI_Gather( sendarray, count, MPI_INT, receivebuffer, count, MPI_INT, 0, MPI_COMM_WORLD);

    // Print values from the rbuf
    if (myrank == 0) {
        // print some values from the root process
        for (int i = 0; i < count; i++) {
            printf("receive buffer value %d : %d\n", i,receivebuffer[i]);
        }
    }

  
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

}
