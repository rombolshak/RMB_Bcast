#include "RMB_Bcast.h"
#include <stdio.h>
#define true 1
#define false 0
#define null 0

int procCount, myRank;

int CalcGoodGroupCount(int current)
{
    int i;
    for (i = 2; i < 257; i *= 2)
    if (current <= i)
	    return i;
}

void DoBcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, int groupCount) {
    
    int goodGroupCount; // round groupCount up to the nearest power of 2
    int len; // length of processors array that will performing bcast
    int receiver; // process which will receive his part of data from us and will retranslate it to others
    
    if (groupCount == 1) return; // we already have data we want
    
    goodGroupCount = CalcGoodGroupCount(groupCount);
    len = goodGroupCount / 2;

    for (receiver = root + 1; (receiver < procCount) && (receiver < root + groupCount);) {
	if (myRank == root)
	    MPI_Send(buffer, count, datatype, receiver, 1, comm);
	else if (myRank == receiver)
	    MPI_Recv(buffer, count, datatype, root, 1, comm, null);

	if ((myRank >= receiver) && (myRank < receiver + len)) {
	    DoBcast(buffer, count, datatype, receiver, comm, len);
	    break;
	}
	receiver += len;
	len /= 2;
    }
}

int RMB_Bcast( void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm ) {
    MPI_Comm_size(comm, &procCount);
    MPI_Comm_rank(comm, &myRank);
    /* check params are correct */
    if (count <= 0) return MPI_ERR_COUNT;
    if ((root < 0) || (root >= procCount)) return MPI_ERR_ROOT;
    if (buffer == NULL) return MPI_ERR_BUFFER;
    /* I don't know how to check datatype and communicator, so lets think everything is ok */

    DoBcast(buffer, count, datatype, root, comm, procCount);
    MPI_Barrier(comm);
    return MPI_SUCCESS;
}
