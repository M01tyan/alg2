#include <stdio.h>
#include <stdlib.h>


#define INFTY 99999


int Warshall(int,int,int);
int Floyd(int,int,int);
int Maggs_Plotkin(int,int,int);
int MST_view(int **, int **, int);


int main(){
  int i,j,k;

  int **Data,n;
  int **d;



 /* input data (size) */
    printf("Input the number of data: ");
    scanf("%d", &n);

 /* Generate arrays (memory allocation)*/
    Data = (int **)malloc(n*sizeof(int *));
    d = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
      Data[i] = (int *)malloc(n*sizeof(int));
      d[i] = (int *)malloc(n*sizeof(int));
    }

 /* input data (matrix)*/
    printf("Input the Adjacency or Distance matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &Data[i][j]);
            d[i][j] = Data[i][j];
        }
    }



  /* Main routines */


      for(k=0; k<n; k++){
        for(i=0; i<n; i++){
          for(j=0; j<n; j++){
            /* Call main routines */
            //Data[i][j] = Warshall(Data[i][j],Data[i][k],Data[k][j]); // Warshall's Algorithm
            //Data[i][j] = Floyd(Data[i][j],Data[i][k],Data[k][j]);  //Floyd's Algorithm

                // Maggs Plotkin Algorithm <MSTを得る処理のために、入力データData[][]とは別途d[][]を作成することを勧める>
            d[i][j] = Maggs_Plotkin(d[i][j],d[i][k],d[k][j]);
          }
        }
      }



    /* Output */
  /*
  int max_d = Data[0][0];
  int max_i;
  int max_j;
  int min_d = Data[0][1];
  int min_i;
  int min_j;
  for(i=0;i<n;i++){
    //int cnt = 0;
    for(j=0;j<n;j++){
      //if(Data[j][i] == 0) cnt++;
      //printf("%d ",Data[i][j]); // For Warshall's Algortihm

      if(Data[i][j]!=INFTY && Data[i][j]!=0){
        if(max_d < Data[i][j]){
          max_d = Data[i][j];
          max_i = i;
          max_j = j;
        }
        if(min_d > Data[i][j]){
          min_d = Data[i][j];
          min_i = i;
          min_j = j;
        }
      }
      else printf("---- "); // For Floyd's Algorithm

    }
    //if(cnt == n){
      //printf("%d \n", i);
    //}
  }
  printf("%d -> %d, %4d\n",max_i+1, max_j+1, max_d);
  printf("%d -> %d, %4d\n",min_i+1, min_j+1, min_d);
  */


  MST_view(Data, d, n);
  /* free allocated memory*/
  for( i = 0 ; i < n ;i++)  free(Data[i]);
  free(Data);



return 0;
}



/* Kernel process of Floyd's & Warshall's Algorithm */

int Warshall(int A_ij,int A_ik,int A_kj){
  /* Arguments A_ij, A_ik, A_kj means A^{k-1}[i][j], A^{k-1}[i][k],A^{k-1}[k][j] at the pseudo code. */
  int Ak_ij; /* A^k[i][j] */

  Ak_ij = A_ij | (A_ik & A_kj);

  return Ak_ij;
}


int Floyd(int D_ij,int D_ik,int D_kj){
  /* Arguments D_ij, D_ik, D_kj means D^{k-1}[i][j], D^{k-1}[i][k],D^{k-1}[k][j] at the pseudo code. */
   int Dk_ij; /* D^k[i][j] */
   int min = D_ij;

   if (D_ik+D_kj < min) min = D_ik + D_kj;
   Dk_ij = min;

   return Dk_ij;
}

int Maggs_Plotkin(int D_ij,int D_ik,int D_kj){
   int Dk_ij;
   int min = D_ij;
   int max = D_ik;

   if(max < D_kj) max = D_kj;
   if(min > max) min = max;
   Dk_ij = min;

   return Dk_ij;
}

int MST_view(int **D0,int **dn,int n){
  int i,j;
  int costs=0;
   for(i=0;i<n;i++){
      for(j=i+1;j<n;j++){//A上で辺があったところが、A^kの全域木に採用されているなら重みを加える
    if(D0[i][j]==dn[i][j] && D0[i][j]!=INFTY){ costs += dn[i][j];
      printf("adopted(%d,%d)  cost:%d   (Data: %d  d: %d)\n",i,j,dn[i][j],D0[i][j],dn[i][j]);
    }
      }
    }
    printf("MST total weights:%d\n",costs);
}
