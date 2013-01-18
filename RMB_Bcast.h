#ifndef RMB_BCAST_H
#define RMB_BCAST_H

#include "mpi.h"

/**
 * Broadcasts a message from the process with rank "root" to all other processes of the communicator
 * @param buffer Data to broadcast
 * @param count Number of entries in buffer
 * @param datatype Data type of buffer
 * @param root Rank of broadcast root
 * @param comm Communicator
 */
int RMB_Bcast( void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm );

#endif
