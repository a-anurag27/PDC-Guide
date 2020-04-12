#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{int i, maxA, minA;
int a[] = {1, 45, 20, 75, 37, 9, 48, 63, 98};
#pragma omp parallel for reduction(max: maxA) reduction(min: minA)
for (int i = 0; i < 9; ++i)
{
	maxA = (maxA > a[i]) ? maxA : a[i];
	minA = (minA < a[i]) ? minA : a[i];
}
printf("Reg: 17BCE0544\n");
printf("Maximum Element in array: %d\nMinimum Element in array: %d\n", maxA, minA);
return 0; 
}
