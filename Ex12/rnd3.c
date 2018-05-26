#include <stdio.h>
#include <time.h>


/* Complete Here !! (Macro Definitions)*/
#define M 2147483647
#define A 48271
#define Q (M/A)
#define R (M%A)

/* Complete Here !! (Variables Declaration) */
static int next=0;
static int x = 1;
static int B[55];

int next_rnd2(void);
int next_rnd3(void);
void init_rnd(void);

int data[100];

int main(){
  int getrand,i;

  init_rnd();

  for(i=0;i<1000;i++){
    data[next_rnd3()%30]++;
    //    printf("%2d: %d\n",i+1,getrand);
  }
  for(i=0;i<30;i++) printf("%d ",data[i]); // sample for listing outputs
  printf("\n");
  return 0;
}

void init_rnd(void){
  int i;
  for (i=0;i<55;i++) B[i] = next_rnd2();
    }

int next_rnd3(void){
  int i,j,k;
  i = (next+31)%55;
  k=(B[i]-B[next]);
  if(k<0){
    k += M;
    k += 1;
  }
  B[next] = k;
  next = (next+1)%55;

  return k;
}

int next_rnd2(void){

  x = A*(x%Q)-R*(x/Q);
  if (x<0) x = x+M;
  
  return x;
}
