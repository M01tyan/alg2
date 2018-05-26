#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INFTY 999999

void compute(int);
void order(int,int);


int *R;     /* matrix size table*/
int **Best; /* Best table */
int **C;    /* Cost table */


int main(){
  int i;
  int status=0,num=0;
  int size,matsize;


  /* IO procedure*/
     R = (int *)malloc(sizeof(int)* MAX);
  Best = (int **)malloc(sizeof(int *)* MAX);
     C = (int **)malloc(sizeof(int *)* MAX);

  for(i=0;i<MAX;i++){
   Best[i] = (int *)malloc(sizeof(int)* MAX);
      C[i] = (int *)malloc(sizeof(int)* MAX);
  }

  printf("Input r1,r2,.... of chain matrices.(r_n*r_n+1)\n");

  i=0;
  while(1){
    printf("Input the r of Matrix %d (M%d) ->",i+1,i+1);
    while(status!=EOF){
     status=scanf("%d",&num);
     if(num<1) printf("Input rational number. (should be positive number)\n->");
     else break;
    }

  if(status==EOF){
    size = i;
    matsize = size-1;
    break;
  }
  R[++i]=num;
  }


  printf("\n\n");

  for(i=0;i<size;i++) printf("r%d = %d ",i+1,R[i+1]);
  printf("\n\n");

  for(i=0;i<size-1;i++) printf("M%d=%d*%d ",i+1,R[i+1],R[i+2]);
  printf("\n\n");





  /* Main routine */
  compute(matsize);


  /* Output */
  order(1, matsize);

  printf("\n\n");
  printf( "(cost): %d\n", C[1][matsize]);



  /* Free allocated memory space */
  for(i=0;i<MAX;i++){
    free(Best[i]);
    free(C[i]);
  }
  free(Best);
  free(C);
return 0;
}





void compute(int n){
  int i,j,k;
  int cost;



//初期化（現段階での最小コストが書き込まれるテーブル（2次元配列）C[][]の''上三角成分''の初期化）
  for ( i = 1;i <= n; i++ ){
    for ( j = i+1; j <= n; j++ ){
      C[i][j] = INFTY;
    }
  }

//初期化（C[][]の''対角成分''を初期化）
 for ( i = 0; i <= n; i++ ) C[i][i] = 0;



//連鎖行列積DP
     for ( j = 1; j <= n ; j++ ){
        for ( i = 1; i <= n - j; i++ ){

           for ( k = i+1; k <= i + j; k++ ){
                 //前のテーブルから更新を行う
                 cost =  C[i][k-1] + C[k][i+j] + R[i]*R[k]*R[i+j+1];// Cはテーブルの中身、 Rは行列のサイズそのもの

                 // どのカッコの付け方が最小コストになるか？
                 if ( cost < C[i][i+j] ){
                     C[i][i+j] =  cost;
                     Best[i][i+j] = k;
                printf("C[%d][%d] = %d, k=%d\n",i,i+j,cost,k);
                 }
         }



      }

    }




}




void order(int i,int j){

  if (i==j) printf("M%d",i);
  else{
    printf("(");
    order(i,Best[i][j]-1);
    order(Best[i][j],j);
    printf(")");
  }
}
