#include <stdio.h>
#include <stdlib.h>

#define NON_PATH -1

int main(){
  int **dp, **non_dp;
  int i, j, index;
  int x_size, y_size;
  int non_path_num, non_x, non_y;
  int total_pattern;

  scanf("%d %d", &x_size, &y_size);
  dp = (int **)malloc(sizeof(int *)* y_size);
  non_dp = (int **)malloc(sizeof(int *)* y_size);
  for(i=0; i<y_size; i++){
    dp[i] = (int *)malloc(sizeof(int)* x_size);
    non_dp[i] = (int *)malloc(sizeof(int)* x_size);
  }

  scanf("%d", &non_path_num);
  for(i=0; i<non_path_num; i++){
  }
  for(i=0; i<non_path_num; i++){
    scanf("%d %d", &non_x, &non_y);
    non_dp[y_size-non_y][non_x-1] = NON_PATH;
  }

  for(i=y_size-1; i>=0; i--){
    dp[i][0] = 1;
    for(j=0; j<x_size; j++){
      if(i == y_size-1){
        dp[i][j] = 1;
        continue;
      }
      dp[i][j] = dp[i][j-1] + dp[i+1][j];
    }
  }
  
  for(i=0; i<y_size; i++){
    for(j=0; j<x_size; j++){
      printf("%8d ", dp[i][j]);
    }
    printf("\n");
  }
  for(i=0; i<y_size; i++){
    for(j=0; j<x_size; j++){
      printf("%3d ", non_dp[i][j]);
    }
    printf("\n");
  }
  
  total_pattern = dp[0][x_size-1];
  for(i=0; i<y_size; i++){
    for(j=0; j<x_size; j++){
      if(non_dp[i][j] == NON_PATH){
        total_pattern -= dp[i][j];
      }
    }
  }

  printf("Number of routes: %d patterns\n", total_pattern);

  return 0;
}
