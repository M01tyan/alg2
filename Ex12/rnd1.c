#include <stdio.h>
#include <stdlib.h>

/* Complete Here !! (Variables Declaration) */
#define M 2147483647

int next_rnd1(void);

static long x = 53402397;
int data[100];

int main(){
  int getrand,i;
  for(i=0;i<1000;i++){
    data[next_rnd1()%30]++;
    //    printf("%d: %d\n",i+1,getrand);
  }

  for(i=0;i<30;i++) printf("%d ",data[i]); // sample for listing outputs
  printf("\n");
  return 0;
}

int next_rnd1(void){
  x = x*65539+125654;
  if((int)x<0){
    x += M;
    x += 1;
  }
  
  return x;
}
