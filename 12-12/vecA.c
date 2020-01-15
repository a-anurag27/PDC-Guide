#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define AS 10

void main()
{
	int *a,*b,*c;
	int n = AS;
	int i;
 
	a = (int *)malloc(sizeof(int) *n);
	b = (int *)malloc(sizeof(int) *n);
	c = (int *)malloc(sizeof(int) *n);
	for(i=0;i<n;i++)
	{
		a[i]=i;
	}
	for(i=0;i<n;i++)
	{
		b[i]=i;
	}
	printf("\n");	
	#pragma omp parallel for schedule (static,3)
	
	for(i=0;i<n;i++)
	{
	c[i] = a[i] + b[i];
	printf("Thread - %d\tElement - %d\n",omp_get_thread_num(),i);	
	}

	printf("\na[i] + b[i] = c[i]\n");
	for(i=0;i<n;i++)
	{
		printf("%d + %d = %d\n",a[i],b[i],c[i]);
	}

	free(a);
	free(b);
	free(c);
}
