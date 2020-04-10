
#include<stdio.h> #include<omp.h>
int main(){
#pragma omp parallel{
printf("Number of Processors : %d\n",omp_get_num_procs()); 
printf("Number of Threads : %d\n",omp_get_num_threads()); 
printf("Number of Maximum Threads : %d\n",omp_get_max_threads()); 
printf("Number of threads in parallel : %d\n",omp_in_parallel()); 
printf("Dynamic : %d\n",omp_get_dynamic());
printf("Nested: %d\n",omp_get_max_active_levels()); 
}
//omp_get_nested() is deprecated as seen in screenshot 
return 0;
}
