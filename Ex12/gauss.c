#include <stdio.h>
#include <math.h>

#define RAND_MAX 2147483647
//乱数生成
extern void my_srand(void);
extern int my_GetRand(void);

int main(){
  int i;
  double g1;
  int data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  double x1, x2;
  //乱数生成
  my_srand();
  for(i=0; i<1000000; i++){
    x1 = (double)my_GetRand()/RAND_MAX;
    x2 = (double)my_GetRand()/RAND_MAX;
    g1 = sqrt(-2*log(x1))*cos(2*M_PI*x2);
    //    printf("%lf %lf %lf ", x1, x2, g1);
    if(g1 < -3) data[0]++;
    else if(g1 < -2) data[1]++;
    else if(g1 < -1) data[2]++;
    else if(g1 < 0) data[3]++;
    else if(g1 < 1) data[4]++;
    else if(g1 < 2) data[5]++;
    else if(g1 < 3) data[6]++;
    else data[7]++;
  }
  for(i=0; i<8; i++){
    printf("%d ", data[i]);
  } printf("\n");
  
  return 0;
}
