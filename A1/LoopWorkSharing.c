#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define CHUNKSIZE 5 
#define N 20
int main (int argc, char *argv[]) 
{
int nthreads, tid, i, chunk;
float a[N], b[N], c[N];
for (i=0; i < N; i++) 
	a[i] = b[i] = i * 2; 
printf("Reg : 17BCE0544\n");
chunk = CHUNKSIZE;
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid) 
	{
	tid = omp_get_thread_num();
	if (tid == 0)
	{
		nthreads = omp_get_num_threads(); 
		printf("Number of threads = %d\n", nthreads); 
	}
	printf("Thread %d Starting...\n",tid);
	#pragma omp for schedule(dynamic,chunk) 
	for (i=0; i<N; i++)
	{
		c[i] = a[i] + b[i];
		printf("Thread %d: c[%d] : %f\n",tid,i,c[i]); 
	}
	}
}
