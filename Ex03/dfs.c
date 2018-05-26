#include <stdio.h>
#include <stdlib.h>

void DFS(int);

int n;         //number of vertex ( 'V' of graph G(V,E) )
int label = 0;     //the order of vertex visiting
int *visited;  //if vertex_i was visited?
int **A;       //Adjacency matrix

int main(){
    int start;
    int i, j;
    /* input number of vertex */
    printf("Input the number of data: ");
    scanf("%d", &n);

    /* memory allocation and initialization */
    visited = (int *)malloc(sizeof(int)*n);
    A = (int **)malloc(sizeof(int *)*n);
    for(i=0 ;i < n;i++){
      A[i] = (int *)malloc(sizeof(int )*n);
      visited[i] = 0;
    }

    printf("Input the Adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    printf("Input the initial node: 1 to %d\n",n);
    scanf("%d", &start);

    printf("The edges in the DFS tree with root %d are:\n", start);
    DFS(start-1);

    /* memory free */
    for(i=0 ;i < n;i++) free(A[i]);
    free(A);
    free(visited);

    return 0;
}

void DFS(int node){
    int t;

    visited[node] = ++label;
    for (t = 0; t < n; t++) {
        if (A[node][t] != 0 && visited[t] == 0) {
            printf("(%d,%d)\n", node+1, t+1);
            DFS(t);   //Recursive call
        }
    }

}
