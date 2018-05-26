#define MAX_COIN 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int coin[4] = {25, 10, 5, 1};

int main(){
  int i,j;
  int *haveCoin, *payCoin;
  haveCoin = (int *)malloc(4*sizeof(int));
  payCoin = (int *)malloc(4*sizeof(int));
  int totalCents=0, totalUse=0, cash;

  printf("Input numbers of each cent(coin).\n->");
  for(i=0; i<4; i++){
    scanf("%d", &haveCoin[i]);
  }
  printf("Input how many cents should you pay?\n->");
  scanf("%d", &totalCents);
  cash = totalCents;

  //Greedy Algorithms
  //25セント->1セントの順番でループ
  //所有している硬貨の枚数から支払い金額を上回らない範囲で最も多い枚数を算出する
  //その硬貨での最大枚数を求めたら{支払額-(硬貨の金額*枚数)}を支払額として次の硬貨で計算
  for(i=0; i<4; i++){
    payCoin[i] = 0;
    for(j=haveCoin[i]; j>0; j--){
      if(coin[i]*j > cash) continue;
      else {
        cash -= coin[i]*j;
        payCoin[i] = j;
        break;
      }
    }
    if(cash == 0) break;
  }
  if(cash != 0) printf("Error: you cannot pay for this value\n");
  else {
    for(i=0; i<4; i++){
      printf("[%dcent] %d used.\n", coin[i], payCoin[i]);
      totalUse += payCoin[i];
    }
    printf("Totally, you used %d coins for %d cents.\n", totalUse, totalCents);
  }
}
