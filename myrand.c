#include <stdio.h>
#include <time.h>


/* Complete Here !! (Macro Definitions)*/
#define M 2147483647
#define A 48271
#define Q (M/A)
#define R (M%A)

/* Complete Here !! (Variables Declaration) */
static int next=0;
static int x;
static int B[55];

int next_rnd2(void);
int next_rnd3(void);
void init_rnd(void);
void my_srand(void);

int data[100];


void init_rnd(void){
  int i;
  for (i=0;i<55;i++) B[i] = next_rnd2();
}

int my_GetRand(void){
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

void my_srand(void){
  time_t stamp;
  struct tm *t;

  stamp = (int)time(NULL);
  t = localtime(&stamp);

  x = t->tm_sec; // seed
  init_rnd();
}
