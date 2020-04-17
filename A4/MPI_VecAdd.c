#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 20000000
#define MASTER 0
double data[ARRAYSIZE];
int main (int argc, char *argv[])
{
int numtasks, taskid, rc, dest, offset, i, j, tag1,tag2, source, chunksize, leftover;
double mysum, sum;
double update(int myoffset, int chunk, int myid); 
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
MPI_Comm_rank(MPI_COMM_WORLD,&taskid); 
printf ("MPI task %d has started... ", taskid);
chunksize = (ARRAYSIZE / numtasks);
leftover = (ARRAYSIZE % numtasks); 
tag2 = 1;
tag1 = 2;
if (taskid == MASTER){
sum = 0;
for(i=0; i<ARRAYSIZE; i++) 
{ 
data[i] = i * 1.0;
sum += data[i];
}
printf("\nInitialized array sum = %e\n",sum);
printf("numtasks= %d \t chunksize= %d \t leftover= %d\n",numtasks,chunksize,leftover);
offset = chunksize + leftover;
for (dest=1; dest<numtasks; dest++) {
MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD); 
MPI_Send(&data[offset], chunksize, MPI_DOUBLE, dest, tag2, MPI_COMM_WORLD); 
printf("Sent %d elements to task %d offset= %d\n",chunksize,dest,offset);
offset = offset + chunksize;
}
offset = 0;
mysum = update(offset, chunksize+leftover, taskid);
for (i=1; i<numtasks; i++) {
source = i;
MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status); 
MPI_Recv(&data[offset], chunksize, MPI_DOUBLE, source, tag2, MPI_COMM_WORLD, &status);
}
MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
printf("Sample results: \n"); 
offset = 0;
for (i=0; i<numtasks; i++) { 
	for (j=0; j<5; j++)
		printf(" %e",data[offset+j]); 
	printf("\n");
	offset = offset + chunksize; 
}
printf("*** Final sum= %e ***\n",sum); 
}
if (taskid > MASTER) { 
source = MASTER;
MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status); 
MPI_Recv(&data[offset], chunksize, MPI_DOUBLE, source, tag2, MPI_COMM_WORLD, &status);
mysum = update(offset, chunksize, taskid);
dest = MASTER;
MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
MPI_Send(&data[offset], chunksize, MPI_DOUBLE, MASTER, tag2, MPI_COMM_WORLD); 
MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER,MPI_COMM_WORLD); 
} 
MPI_Finalize();
} 
double update(int myoffset, int chunk, int myid) 
{
int i;
double mysum=0;
for(i=myoffset; i < myoffset + chunk; i++) 
{
data[i] = data[i] + (i * 1.0);
mysum += data[i];
}
printf("\nTask %d mysum = %e\n",myid,mysum);
return(mysum);
}
