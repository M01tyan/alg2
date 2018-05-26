#include <stdio.h>
#include <stdlib.h>
#define INFTY 99999

typedef struct{//ある頂点への（最短）距離を管理
  int key;
  int dist;
}DIST;

void construct_2(DIST *, int);
void downheap(DIST *, int, int);

void Dijkstra(int,int);
void insert(DIST *, DIST, int);
DIST delete_root(DIST *,int *);
void replace(DIST *, DIST, int, int);

int *label;//vartex (reached or unreached), called "S" in the lecture slide
int **D;   //costs (distance matrix)
int *d;    //distance from start (root) node (sum of the costs)
int *adj;  //the parent node in shortest path spanning tree
DIST *data; //d[]をヒープとして持つための配列

//d[i]に対応する値がヒープによってdata[]のどこにあるか分からなくならないように
//指し示すindexの配列 ind[]
int *ind;


int main(){
  int i,j;
  int start;
  int n;

 /* input data (size) */
    printf("Input the number of data: ");
    scanf("%d", &n);

 /* Generate arrays (memory allocation)*/
    label = (int *)malloc(n*sizeof(int));
        d = (int *)malloc(n*sizeof(int));
      adj = (int *)malloc(n*sizeof(int));
        D = (int **)malloc(n*sizeof(int *));
     data = (DIST *)malloc((n+1)*sizeof(DIST));
     ind = (int *)malloc((n+1)*sizeof(int));

    for (i=0;i<n;i++) D[i] = (int *)malloc(n*sizeof(int));


 /* input data (matrix)*/
    printf("Input the Distance matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &D[i][j]);
        }
    }

 /* input data (inital node)*/
    printf("Input the initial node: ");
    scanf("%d", &start);

 /* Call main routines of [ Dijkstra's Algorithm ] */
    Dijkstra(start,n);

 /* Show results */

    printf("\nresult:\n");
    for (i = 0 ; i < n ; i++ ) {
        if(i==start) printf("vertex %c -> root\n",i+65);
        else printf("vertex %c -> %d (visited_order : %d)\n",i+65,d[i] ,label[i]);
    }

  /* free allocated memory*/
    for ( i = 0 ; i < n ;i++)  free(D[i]);
    free(label);
    free(adj);
    free(D);
    free(d);
    free(data);
    free(ind);
    return 0;
}


void Dijkstra(int root,int n){
  int i,j;
  int min_cost,min_node;
  int visited_order = 0;
  int V_S=0;//ヒープに入っているデータの個数

  DIST newnode;//ヒープに入れるため（引数の準備）
  DIST min;//ヒープから取り出したもの（戻り値の保管）

  // **** initialization ****
  //  S = {s}; d[s] = 0;
  //  d[root] = 0;
  // ************************
    for ( i = 0; i < n; i++) {
        label[i] = 0;
        d[i] = D[root][i];
        ind[i+1]=-1;

        if (i!=root && d[i]!=0 && d[i]!=INFTY) {
            data[V_S+1].key = i;
            data[V_S+1].dist = d[i];
            ind[i+1]=V_S+1;
            V_S++;
        }
    }
    adj[root] = -1;


    label[root] = ++visited_order;
    construct_2(data, n);  //全体をヒープにする（前処理）


    // while (S != V) {
    while (visited_order < n) { // S !=V  -->  |V| < |S|

        min = delete_root(data, &n); //ヒープの最小値を取り出す
        min_cost = min.dist;
        min_node = min.key;

        if ( min_cost == INFTY ) continue;// no edges
        // add w to S;
        label[min_node]= ++visited_order;

        //for (v in V-S)
        for ( i = 0; i < n; i++ ) {

            //d[v] = min{d[v],d[w]+D[w,v]};
            if ( d[i] > d[min_node] + D[min_node][i] ) {
                if (d[i]==INFTY) {
                    ind[i+1]= V_S+1;
                    d[i] = d[min_node] + D[min_node][i];
                    adj[i] = min_node;
                    newnode.dist = d[i];
                    newnode.key = i;
                    insert(data,newnode,++V_S);
                }
                else {
                    d[i] = d[min_node] + D[min_node][i]; //(上と同じ)
                    adj[i] = min_node; //(上と同じ)
                    newnode.dist = d[i];
                    newnode.key = i;
                    replace(data,newnode,ind[i+1],V_S);//既存の値より短い辺が出現（書き換えた場合）
                }
            }
        }
    }
}


/*

＜ヒープ部分＞

本質的にはEx02で作ったものと同じだが、
配列Ａや一時保存変数ｖが構造体"DIST型"であることに注意すること。
（距離を保持している構造体DISTのメンバー dist を見てヒープ条件のチェックをすることになる）

また、dijkstraで既存の値を書き換えたときに、ヒープが壊れてしまうので壊れた部分については
ヒープ化しなおす必要があるが、書き換えた値がヒープのどこに行ってしまったかが
そのままでは分からなくなってしまうため、index配列（ind[])を使って i番目の頂点への値の最小値が
ヒープ内のどこにあるかind[i]で指し示す。

primやkruskalをヒープ実装するのに比べると、ここが大変。
*/


void construct_2(DIST *A, int n) {
  int i,j;

    for (i=n/2; i>=1; i--) {
        downheap(A, i, n);
    }
}

void upheap(DIST *A, int k){
  DIST v;
  int tmp;

    v=A[k];
    tmp = ind[data[k].key+1];

    while (k>1 && A[k/2].dist>=v.dist) {
        ind[A[k/2].key+1]=ind[A[k].key+1];
        A[k]=A[k/2];
        k=k/2;
    }
    A[k]=v;
    ind[A[k].key+1]=tmp;
}


void downheap(DIST *A, int k, int n){
  int j, tmp,tmp2;
  int tmp_pos;
  DIST v;

    tmp = A[k].key+1;
    tmp_pos = k;
    v=A[k];
    tmp2 = A[k].dist;

    while (k<=n/2) {
        j=k+k;
        if (j<n && A[j].dist > A[j+1].dist ) j++;
        if (tmp2 <= A[j].dist) break;

        ind[A[j].key+1]=ind[A[k].key+1];
        A[k]=A[j];

        k=j;
    }
    A[k]=v;
    ind[tmp]=k;  //ind[]もヒープの値が遷移するのと同じように移動させる
}


void insert(DIST *A, DIST v, int n){
    A[n] = v;
    upheap(A, n);
}

DIST delete_root(DIST *A,int *n){
    DIST v = A[1];

    ind[data[*n].key+1] = 1;
    ind[data[1].key+1]= -1;

    A[1] = A[*n];
    (*n)--;
    downheap(A, 1, *n);
    return v;
}

/*
replace()

Ex02ではA[1]の要素を任意の値に書き換える関数だったが、
Dijkstraの処理の過程で、「指定の頂点までの最短距離を更新する」処理があるので
任意の頂点 p の値を書き換えられるように変更した。

ヒープが壊れる場所が p に変わるだけなので、あとはdownheapに任せるだけ。
*/

void replace(DIST *A, DIST v, int p, int n){
    A[p] = v;
    downheap(A, p, n);
}
