#include <stdio.h>
#include <stdlib.h>

#define A 48271
#define M 2147483647
#define Q (M/A)
#define R (M%A)
/* Complete Here !! (Variables Declaration) */
static int x = 1;


int next_rnd2(void);

int data[100];

int main(){
  int getrand,i;

  for(i=0;i<1000;i++){
    data[next_rnd2()%30]++;
    //    printf("%2d: %d\n",i+1,getrand);
  }

  for(i=0;i<30;i++) printf("%d ",data[i]); // sample for listing outputs
  printf("\n");
  return 0;
}

int next_rnd2(void){

  x = A*(x%Q)-R*(x/Q);
  if (x<0) x=x+M;
  
  return x;
}
