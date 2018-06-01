#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000

extern int my_GetRand(void);
extern void my_srand(void);

int main(){
  int i,j;
  double *A;
  double tmp;
  double st,et;

  A = malloc(sizeof(double)*(N+1));


  my_srand();
  for(i=0;i<N;i++){
    A[i]=my_GetRand()/1000000;
  }

  /*参考用に、最初の30個分のデータのみ出力*/
  for(i=1;i<=30;i++){
    printf("%d. %f\n",i,A[i]);
  }


  st = omp_get_wtime();

  /* Odd even sort ここから */

  for(j=0;j<=N/2;j++){

#pragma omp parallel for private(tmp)
    for(i=1;i<=(2*(N/2))-1;i+=2){
      if(A[i]>A[i+1]){
	tmp = A[i];
	A[i]=A[i+1];
	A[i+1]=tmp;
      }
    }

#pragma omp parallel for private(tmp)
    for(i=2;i<=2*((N-1)/2);i+=2){
      if(A[i]>A[i+1]){
	tmp = A[i];
	A[i]=A[i+1];
	A[i+1]=tmp;
      }
    }


  }

  /* Odd even sort ここまで */
  et = omp_get_wtime();



  /*参考用に、ソート後の昇順データ最初の30個分のデータのみ出力*/
  printf("After sorted\n");
  for(i=1;i<=30;i++){
    printf("%d. %f\n",i,A[i]);
  }
  printf("elapsed time: %f\n",et-st);


  free(A);
  return 0;
}
