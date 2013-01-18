#include "mpi.h"
#include "RMB_Bcast.h"
#include <stdio.h>
#include <stdlib.h>

double * genData(int length) {
    int i;
    double *data = malloc(length * sizeof(double));
    for (i = 0; i < length; ++i)
        data[i] = i;
    return data;
}

int checkDataIsCorrect(double *data, int length) {
    int i;
    for (i = 0; i < length; ++i)
	if (data[i] != i)
	    return 0;
    return 1;
}

void getTimesOfBroadcasting(double *data, int dataLength, double* myTime, double* mpiTime, int myid, int numprocs) {
    double start, end, span;
    int i;

    start = MPI_Wtime();
    for (i = 0; i < 1000; ++i)
	    MPI_Bcast(data, dataLength, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();
    span = end - start;
    MPI_Reduce(&span, &span, 1, MPI_DOUBLE, MPI_SUM, 2, MPI_COMM_WORLD);
    if (myid == 2)
	    *mpiTime = span / numprocs;
    
    start = MPI_Wtime();
    for (i = 0; i < 1000; ++i)
	    RMB_Bcast(data, dataLength, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();
    span = end - start;
    MPI_Reduce(&span, &span, 1, MPI_DOUBLE, MPI_SUM, 2, MPI_COMM_WORLD);
    if (myid == 2)
	    *myTime = span / numprocs;
}

int main( int argc, char *argv[])
{
    int myid, numprocs;
    int *dataLength, i;
    double *data;
    double myTime, mpiTime;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    dataLength = (int*)malloc(7 * sizeof(int));
    dataLength[0] = 16;
    dataLength[1] = 256;
    dataLength[2] = 512;
    dataLength[3] = 1024;
    dataLength[4] = 1024 * 4;
    dataLength[5] = 1024 * 8;
    dataLength[6] = 1024 * 16;

    for (i = 0; i < 7; ++i) {
    	data = genData(dataLength[i]);
    	getTimesOfBroadcasting(data, dataLength[i], &myTime, &mpiTime, myid, numprocs);
    	if (myid == 2)
    	    printf("Data length: %d, my time: %f seconds, MPI time: %f seconds, correct: %d\n",
    		   dataLength[i], myTime, mpiTime, checkDataIsCorrect(data, dataLength[i]));
    	free(data);
    }
    
    MPI_Finalize();
    return 0;
}
