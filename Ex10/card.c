#include <stdio.h>
#include <stdlib.h>

#define MAX_COST 50
#define CARD_NUM 13



int main(){
  int **dp;
  int *power, *cost;
  int i, j, index;
  int total_card = 0, total_cost = 0, total_power = 0;

  dp = (int **)malloc(sizeof(int *)* CARD_NUM+1);
  power = (int *)malloc(sizeof(int)* CARD_NUM+1);
  cost = (int *)malloc(sizeof(int)* CARD_NUM+1);
  for(i=0; i<CARD_NUM+1; i++){
    dp[i] = (int *)malloc(sizeof(int)* MAX_COST+1);
  }
  power[0] = 0; cost[0] = 0;
  printf("Input the power and cost of cards:\n");
  for(i=1; i<CARD_NUM+1; i++){
    scanf("%d %d", &power[i], &cost[i]);
  }

  for(i=1; i<CARD_NUM+1; i++){
    dp[i][0] = 0;
    for(j=0; j<MAX_COST+1; j++){
      dp[i][j] = dp[i-1][j];
      index = j - cost[i];
      if(index < 0) continue;
      if(dp[i-1][j] < dp[i-1][index]+power[i])
        dp[i][j] = dp[i-1][index]+power[i];
    }
  }


  j = MAX_COST;
  for(i=CARD_NUM; i>0; i--){
    index = j - cost[i];
    if(index < 0){
      printf("Card %2d is not used.\n", i);
      continue;
    }
    if(dp[i][j] == dp[i-1][index]+power[i]){
      printf("Card %2d (pow: %2d, cost: %2d) is used.\n", i, power[i], cost[i]);
      total_card++;
      total_cost += cost[i];
      total_power += power[i];
      j -= cost[i];
    } else {
      printf("Card %2d is not used.\n", i);
    }
  }
  printf("My Best deck has %d cards (Cost: %d, Power: %d)\n", total_card, total_cost, total_power);


  return 0;
}
