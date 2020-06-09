#include "mpi.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#define LIMIT 2500000 /* Increase this to find more primes */ 
#define FIRST 0 /* Rank of first task */
int isprime(int n) {
	int i,squareroot;
	if (n>10) {
		squareroot = (int) sqrt(n);
		for (i=3; i<=squareroot; i=i+2)
			if ((n%i)==0) 
				return 0;
		return 1;
	}
	else
		return 0; 
}
int main (int argc, char *argv[])
{
	int ntasks, rank, n, pc, pcsum, foundone, maxprime, mystart, stride; 
	double start_time,end_time;
	
	MPI_Init(&argc,&argv); 
	MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
	MPI_Comm_size(MPI_COMM_WORLD,&ntasks);
	if (((ntasks%2) !=0) || ((LIMIT%ntasks) !=0)) 
	{
		printf("Sorry - this exercise requires an even number of tasks.\n"); 
		printf("evenly divisible into %d. Try 4 or 8.\n",LIMIT); 
		MPI_Finalize();
		exit(0);
	}
	start_time = MPI_Wtime(); 
	mystart = (rank*2)+1; 
	stride = ntasks*2; 
	pc=0;
	foundone = 0;
	
	if (rank == FIRST) {
	printf("\nUsing %d tasks to scan %d numbers\n",ntasks,LIMIT);
	pc = 4; 
	for (n=mystart; n<=LIMIT; n=n+stride) 
	{
      		if (isprime(n)) 
		{
         		pc++;
			foundone = n;
			printf("%d\n",foundone);
		}
	}
	MPI_Reduce(&pc,&pcsum,1,MPI_INT,MPI_SUM,FIRST,MPI_COMM_WORLD);
	MPI_Reduce(&foundone,&maxprime,1,MPI_INT,MPI_MAX,FIRST,MPI_COMM_WORLD); 
	end_time=MPI_Wtime();
	printf("Done. Largest prime is %d \nTotal primes %d\n",maxprime,pcsum); 
	printf("Wallclock time elapsed: %.2lf seconds\n\n",end_time-start_time); 
	}

	if (rank > FIRST) {
		for (n=mystart; n<=LIMIT; n=n+stride) 
		{ 
			if (isprime(n)) {
				pc++;
				foundone = n;
				printf("%d\n",foundone);
			}
		}
		MPI_Reduce(&pc,&pcsum,1,MPI_INT,MPI_SUM,FIRST,MPI_COMM_WORLD);
		MPI_Reduce(&foundone,&maxprime,1,MPI_INT,MPI_MAX,FIRST,MPI_COMM_WORLD); 
	}
	MPI_Finalize();
	printf("\n17BCE0190 - Vraj");
}
