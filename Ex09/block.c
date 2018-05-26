#include <stdio.h>
#include <stdlib.h>

#define BASE 2//Strassenの性能を出すためには、この値の調整が重要
void FindPlace(int **,int,int,int);
void fourBlock(int **,int,int,int);


int block_id=1;//置いたＬ字型ブロックを個々に識別できるように

int main(int argc,char **argv){
  int i,j,n;
  int **Board;//正方格子
  int hole_x,hole_y;//１個のブロックが最初から置かれている正方格子上の場所

  if(argc!=4){//初期化関係
   fprintf(stderr,"Error: Input arguments were incorrect.\n");
   exit(1);
  }
  hole_x = atoi(argv[1]);//１個のブロックで塞いだｘ座標
  hole_y = atoi(argv[2]);//１個のブロックで塞いだｙ座標
  n = atoi(argv[3]); //正方格子のサイズ（２のべき乗にすること）

  if(!(hole_x>=0 && hole_x<n)|| !(hole_y>=0 && hole_y<n)){
   fprintf(stderr,"Error: The coodinates of blank (%d,%d) what you input was incorrect;\nThe acceptable range is 0 to %d.\n",hole_x,hole_y,n);
   exit(2);
  }

  Board = (int **)malloc(sizeof(int *)*n);
  for(i=0;i<n;i++) Board[i] = (int *)malloc(sizeof(int)*n);

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(i==hole_y&&j==hole_x)Board[i][j]=-1;//ブロックが最初に置かれている場所は -1 とする
      else Board[i][j] = 0; // 0 の場所にＬ字型ブロックを置いていく
    }
  }

  printf("Board_Initialization:\n");
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%2d",Board[i][j]);
      if(j!=n-1)printf(" ");
    }
    printf("\n");
  }

  FindPlace(Board,n,hole_x,hole_y);//処理本体

  printf("Print_Answer:\n");//出力
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%2d",Board[i][j]);
      if(j!=n-1)printf(" ");
    }
    printf("\n");
  }
  for(i=0;i<n;i++) free(Board[i]);
  free(Board);
  return 0;
}


void FindPlace(int **Board,int size,int h_x,int h_y){
/*
この関数は、再帰呼び出しになるので、Boardは各部分問題の時点での大きさ(size)となる。
既にブロックが置かれている場所はh_xとh_yで指定する
Strassen と同様、コードの配置（処理の流れ）は以下のようになるはずである
極小まで分解されたときの処理（再帰の打ち切り）⇒ 部分問題用の配列確保 ⇒ 再帰に持ち込むための準備の処理 ⇒ 再帰呼び出し
*/
  int i, j, mid, a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y;
  int **A, **B, **C, **D;

  if (size <= BASE){//行列がある規定のサイズ以下になったら、通常の乗算に持ち込む
   fourBlock(Board, size, h_x, h_y);
   return;
  }

  mid = size/2;
  A = (int **)malloc(mid * sizeof(int));
  B = (int **)malloc(mid * sizeof(int));
  C = (int **)malloc(mid * sizeof(int));
  D = (int **)malloc(mid * sizeof(int));
  for(i=0; i<mid; i++){
    A[i] = (int *)malloc(mid * sizeof(int));
    B[i] = (int *)malloc(mid * sizeof(int));
    C[i] = (int *)malloc(mid * sizeof(int));
    D[i] = (int *)malloc(mid * sizeof(int));
  }

  if(mid-1 < h_x && mid-1 < h_y){
    Board[mid-1][mid-1] = block_id;
    Board[mid][mid-1] = block_id;
    Board[mid-1][mid] = block_id++;
  } else if(mid-1 >= h_x && mid-1 < h_y){
    Board[mid-1][mid-1] = block_id;
    Board[mid-1][mid] = block_id;
    Board[mid][mid] = block_id++;
  } else if(mid-1 < h_x && mid-1 >= h_y){
    Board[mid-1][mid-1] = block_id;
    Board[mid][mid-1] = block_id;
    Board[mid][mid] = block_id++;
  } else if(mid-1 >= h_x && mid-1 >= h_y){
    Board[mid-1][mid] = block_id;
    Board[mid][mid-1] = block_id;
    Board[mid][mid] = block_id++;
  }
  for(i=0; i<mid; i++){
    for(j=0; j<mid; j++){
      A[i][j] = Board[i][j];
      B[i][j] = Board[i][j+mid];
      C[i][j] = Board[i+mid][j];
      D[i][j] = Board[i+mid][j+mid];
      if(Board[i][j] != 0){
        a_x = j;
        a_y = i;
      }
      if(Board[i][j+mid] != 0){
        b_x = j;
        b_y = i;
      }
      if(Board[i+mid][j] != 0){
        c_x = j;
        c_y = i;
      }
      if(Board[i+mid][j+mid] != 0){
        d_x = j;
        d_y = i;
      }
    }
  }

  FindPlace(A, mid, a_x, a_y);
  FindPlace(B, mid, b_x, b_y);
  FindPlace(C, mid, c_x, c_y);
  FindPlace(D, mid, d_x, d_y);


  for(i=0; i<mid; i++){
    for(j=0; j<mid; j++){
      Board[i][j] = A[i][j];
      Board[i][j+mid] = B[i][j];
      Board[i+mid][j] = C[i][j];
      Board[i+mid][j+mid] = D[i][j];
    }
  }
/*
  printf("---------------------------\n");
  for(i=0; i<size; i++){
    for(j=0; j<size; j++){
      printf("%d ", Board[i][j]);
    }
    printf("\n");
  }
*/
}


void fourBlock(int **Board, int size, int h_x, int h_y){
  int i, j, mid;

  mid = size/2;
  if(mid == h_x && mid == h_y){
    Board[mid-1][mid-1] = block_id;
    Board[mid][mid-1] = block_id;
    Board[mid-1][mid] = block_id++;
  } else if(mid != h_x && mid == h_y){
    Board[mid-1][mid-1] = block_id;
    Board[mid-1][mid] = block_id;
    Board[mid][mid] = block_id++;
  } else if(mid == h_x && mid != h_y){
    Board[mid-1][mid-1] = block_id;
    Board[mid][mid-1] = block_id;
    Board[mid][mid] = block_id++;
  } else if(mid != h_x && mid != h_y){
    Board[mid][mid-1] = block_id;
    Board[mid-1][mid] = block_id;
    Board[mid][mid] = block_id++;
  }
}
