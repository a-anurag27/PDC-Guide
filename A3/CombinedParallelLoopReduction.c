#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
int   i, n, tid;
float a[100], b[100], sum;
printf("Reg: 17BCE0544\n");
/* Inittializing the Array */
n = 12;
for (i=0; i < n; i++)
  a[i] = b[i] = i * 1.0;
sum = 0.0;
#pragma omp parallel for reduction(+:sum)
for (i=0; i < n; i++)
{
    tid = omp_get_thread_num();
    sum = sum + (a[i] * b[i]);
    printf("TID: %d \t i: %d\n",tid,i);
}
printf("\tSum = %f\n",sum);

}
