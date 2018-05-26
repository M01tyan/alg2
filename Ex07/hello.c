#define N 4
 
#include <stdio.h>
#include <omp.h>
 
int main(){
  int i;
  
  printf("Number of processors: %d\n",omp_get_num_procs()); 
  printf("Max threads: %d\n",omp_get_max_threads());
 
 
// Compute sequentially（逐次）
  for(i=0;i<N;i++){
     printf("%d) Hello! I am thread %d.\n",i,omp_get_thread_num());
  }
 
  printf("\n\n");
 
// Compute in parallel（並列）
  #pragma omp parallel for
  for(i=0;i<N;i++){
     printf("%d) Hello! I am thread %d.\n",i,omp_get_thread_num());
  }
 
return 0;
}
