#define N 100000000
   
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h> 
 
int main(){
  int i ,err;
  int *A,sum=0;
  double ave;
  double st,et;
    
  /* Initialization step */
  printf("Number of processors: %d\n",omp_get_num_procs()); 
  printf("Max threads: %d\n",omp_get_max_threads());
  
  A = (int *)malloc(N * sizeof(int));
 
  srand(time(NULL));
  for(i=0;i<N;i++){
   A[i]=rand()%1000;
  }
 
  st = omp_get_wtime();
// Compute sequentially（逐次）
  for(i=0;i<N;i++){
    sum+=A[i];
  } 
  ave = (double)sum/N;
  et = omp_get_wtime();
 
  printf("sequetially: %5.3f sec.\n",et-st);
  printf("ave:%f\n",ave);
 
  printf("\n\n");
  
 
 
 
  sum=0;
 st = omp_get_wtime();
// Compute in parallel ver.1
#pragma omp parallel for 
  for(i=0;i<N;i++){
    sum+=A[i];
  } 
 ave = (double)sum/N;
 et = omp_get_wtime();
 
 printf("at parallel1: %5.3f sec.\n",et-st);
 printf("ave(omp1):%f\n",ave);
 
 
 
 
sum=0;
st = omp_get_wtime();
// Compute in parallel ver.2 
#pragma omp parallel for private(sum)
  for(i=0;i<N;i++){
    sum+=A[i];
  } 
 ave = (double)sum/N;
 et = omp_get_wtime();
 
 printf("at parallel2: %5.3f sec.\n",et-st);
 printf("ave(omp2):%f\n",ave);
 
 
 
 
 
 sum=0;
 st = omp_get_wtime();
// Compute in parallel ver.3
#pragma omp parallel for reduction(+:sum)
  for(i=0;i<N;i++){
    sum+=A[i];
  } 
 ave = (double)sum/N;
 et = omp_get_wtime();
 
 printf("at parallel3: %5.3f sec.\n",et-st);
 printf("ave(omp3):%f\n",ave);
  
 free(A);
 
 return 0;
}
