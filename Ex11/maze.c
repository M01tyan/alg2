#include <stdio.h>
#include <stdlib.h>

#define PASSABLE 1       //mazesolve()の戻り値はこれらのどちらかにすること
#define CANNOT_PASS 0

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int mazesolve(int,int);


int **Maze;
int **Solution;
int nx,ny;
int s_x,s_y;
int g_x,g_y;

int searched_id=0;      //探索順番記録用
int dir = RIGHT;
int total_search = 0;

FILE *fp;

int main(int argc,char** argv){
  int i,j;
  int check;

  if(argc!=2){
    fprintf(stderr,"error: Give the argument of inputting file for this program.\n");
    exit(1);
  }
  fp = fopen(argv[1],"r");
  if(fp==NULL){
    fprintf(stderr,"error: no such file named '%s'.\n",argv[1]);
    exit(2);
  }

  fscanf(fp,"%d %d",&nx,&ny);
  // Maze[y][x]
  Solution = (int **)malloc(sizeof(int *)*ny);
  Maze = (int **)malloc(sizeof(int *)*ny);
  for(j=0;j<ny;j++){
    Maze[j]=(int *)malloc(sizeof(int)*nx);
    Solution[j]=(int *)malloc(sizeof(int)*nx);
    for(i=0;i<nx;i++){
      fscanf(fp,"%d", &Maze[j][i]);
      Solution[j][i]=0;
    }
  }
  //printf("Where to Start?->");
  fscanf(fp,"%d %d",&s_x,&s_y);
  //printf("Where is the Goal?->");
  fscanf(fp,"%d %d",&g_x,&g_y);
  fclose(fp);
  printf("\n");

/*
  for(j=0;j<ny;j++){//check input case
    for(i=0;i<nx;i++){
      printf("%d", Maze[j][i]);
      if(i==nx-1)printf(" ");
      }
    if(j!=ny)printf("\n");
    }
*/

  check = mazesolve(s_x, s_y);
  if(check == CANNOT_PASS){
    printf("There is no way to solve this maze.\n");
  }
  else{
    printf("route length %d\n", searched_id);
    printf("Total Search %d\nSolution\n", total_search);
    for(j=0;j<ny;j++){// output the solution
      for(i=0;i<nx;i++){
        printf("%5d", Solution[j][i]);
        if(i==nx-1)printf(" ");
        }
      if(j!=ny-1)printf("\n");
      }
      printf("\n");
  }


  for(j=0;j<ny;j++){
    free(Maze[j]);
    free(Solution[j]);
  }
  free(Maze);
  free(Solution);

  return 0;
}



int mazesolve(int search_x, int search_y){
  int index_x, index_y;
  int i;

  total_search++;
  /*
    int k,j;
    for (k = 0; k < ny; k++) {
    for (j = 0; j < nx; j++) printf("%3d ", Solution[k][j]);
    printf("\n");
  }
    printf("--------------------------------------------\n");
  */

  if(search_x == g_x && search_y == g_y){
    Solution[search_y][search_x] = ++searched_id;
    return PASSABLE;
  }
  if(Maze[search_y][search_x] == 1 && Solution[search_y][search_x] == 0){
    Solution[search_y][search_x] = ++searched_id;
    for(i=0; i<4; i++){
      if(dir == RIGHT){
        index_x = search_x + 1;
        if(index_x < nx){
          if(mazesolve(index_x, search_y) == PASSABLE) return PASSABLE;
          else dir = (dir+1)%4;
        } else dir = (dir+1)%4;
      }
      if(dir == DOWN){
        index_y = search_y + 1;
        if(index_y < ny){
          if(mazesolve(search_x, index_y) == PASSABLE) return PASSABLE;
          else dir = (dir+1)%4;
        } else dir = (dir+1)%4;
      }
      if(dir == LEFT){
        index_x = search_x - 1;
        if(index_x >= 0){
          if(mazesolve(index_x, search_y) == PASSABLE) return PASSABLE;
          else dir = (dir+1)%4;
        } else dir = (dir+1)%4;
      }
      if(dir == UP){
        index_y = search_y - 1;
        if(index_y >= 0){
          if(mazesolve(search_x, index_y) == PASSABLE) return PASSABLE;
          else dir = (dir+1)%4;
        } else dir = (dir+1)%4;
      }
    }
  } else return CANNOT_PASS;

  Solution[search_y][search_x] = -1;
  searched_id--;
  return CANNOT_PASS;
}