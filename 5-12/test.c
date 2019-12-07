//**Environment Variable**
//export OMP_NUM_THREADS=20
// FOR MAC OS
// brew install libomp
// clang -Xpreprocessor -fopenmp -lomp test.c

//gcc test.h -fopenmp
//./a.out


#include<stdio.h>

//Header File
#include<omp.h>

void main()
{

	int tid,nt;

	//Set threads through runtime
	omp_set_num_threads(10);
	
	//Directive to Start OMP
	#pragma omp parallel
	
	{
		//Some inbuilt functions
		tid = omp_get_thread_num();
		nt = omp_get_num_threads();
		printf("Hello World %d / %d\n",tid,nt);
	}

}
