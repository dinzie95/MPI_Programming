#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {

MPI_Init(&argc,&argv);

int myrank, numprocs;

/*variables used for gathering timing statistics*/
double mytime, maxtime, mintime, avgtime;

MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

MPI_Barrier(MPI_COMM_WORLD); /*synchronize all processes*/

mytime = MPI_Wtime(); /*get time just before work section */

printf("Working in processor %d\n",myrank);

mytime = MPI_Wtime() - mytime; /*get time just after work section*/

/*compute max, min, and average timing statistics*/
MPI_Reduce(&mytime, &maxtime, 1, MPI_DOUBLE,MPI_MAX, 0, MPI_COMM_WORLD);
MPI_Reduce(&mytime, &mintime, 1, MPI_DOUBLE, MPI_MIN, 0,MPI_COMM_WORLD);
MPI_Reduce(&mytime, &avgtime, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);

if (myrank == 0) {
avgtime /= numprocs;
printf("Min: %lf Max: %lf Avg: %lf\n", mintime, maxtime,avgtime);
}

MPI_Finalize();
}
