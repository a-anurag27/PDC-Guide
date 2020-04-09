#include<stdio.h> 
#include<omp.h>
int main() 
{
	int n,a[100],i;
	omp_set_num_threads(2);
	printf("Reg : 17BCE0544\n");
	printf("Enter the number of terms of Fibonacci Series:\n"); 
	scanf("%d",&n);
	a[0]=0;
	a[1]=1;
	#pragma omp parallel
	{	
		#pragma omp single 
		for(i=2;i<n;i++)
		{
		a[i]=a[i-2]+a[i-1];
		printf("Fibonacci number: %d is computed by TID: %d\n",i+1,omp_get_thread_num()); 
		}
		#pragma omp barrier 
		#pragma omp single
		{
		printf("The elements of fibonacci series are\n"); 
		for(i=0;i<n;i++)
			printf("Fib Seq: %d is Displayed by TID: %d\n",a[i],omp_get_thread_num());
		} 
	}
	return 0; 
}
