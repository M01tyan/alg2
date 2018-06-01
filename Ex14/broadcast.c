#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
/*
プロセッサ(＝OpenMPの場合スレッド)の数
サンプルプログラムの場合、プロセッサとデータが一対一対応となっている場合の放送アルゴリズム
*/
#define NUM_PROCESSOR 32

int mypow(int, int);//For 2^n

int main(){
  int i,j;

  double D = 1.41421356;
  double loc;
  double A[NUM_PROCESSOR+1];

  omp_set_num_threads(NUM_PROCESSOR);

  loc = D;
  A[1] = loc;

  for(i=0; i <= log2(NUM_PROCESSOR)-1; i++){
#pragma omp parallel for private(loc)
    for(j = mypow(2,i)+1 ; j <= mypow(2,i+1); j++){
      loc = A[j-mypow(2,i)];
      A[j] = loc;
    }
  }


  printf("Result of Broadcasting D = %f to A[]:\n",D);
  for(i=1;i<=NUM_PROCESSOR;i++){
    printf("A[%d] = %f\n",i,A[i]);
  }


  return 0;
}


int mypow(int x, int n){
  int i;
  int res = 1;

  for(i=0;i<n;i++) res *= x;
  return res;
}
