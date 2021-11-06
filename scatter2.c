#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>


int main (int argc, char *argv[]) {

MPI_Comm comm;
int gsize,*sendbuf;
int root, rank,rbuf[100];

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size( comm, &gsize);

srand(time(NULL));

sendbuf = (int *) malloc(gsize*100*sizeof(int));

for (int i = 0; i < 100; i++) {
        sendbuf[i] = (rand() % 100);
    }

MPI_Scatter( sendbuf, 100, MPI_INT, rbuf, 100, MPI_INT, root, comm);

printf("rank= %d Results: %d %d %d %d\n",rank,rbuf[0],
rbuf[1],rbuf[2],rbuf[3]);

MPI_Finalize();
}
