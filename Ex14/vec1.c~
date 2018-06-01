//8要素を持つ2つの配列を演算する
#include <stdio.h>
#include <immintrin.h>
#define N 8

extern int my_GetRand(void);
extern void my_srand(void);


int main(){
  int i;
  float *a,*b,*c; // 普通の配列だが、ベクトル演算を有効に働かせるために、float（単精度浮動小数点）にする
  __m256 vec_a,vec_b,vec_c; //ベクトル演算専用のレジスタ（float 8個分を持つ配列）

  my_srand();

  a = (float *)_mm_malloc(sizeof(float)*N,32); // ベクトル演算を行う配列は専用のmalloc
  b = (float *)_mm_malloc(sizeof(float)*N,32); // メモリ空間上に、明示的にきれいに整列しておく
  c = (float *)_mm_malloc(sizeof(float)*N,32); //
  for(i=0;i<N;i++){
    a[i] = (float)my_GetRand()/214748364; // 0.0 ～ 10.0 の擬似乱数を想定
    b[i] = (float)my_GetRand()/214748364;
  }

  //計算前データ表示
  printf("vector A:\n");
  for(i=0;i<N;i++) printf("%f ",a[i]);
  printf("\n");
  printf("vector B:\n");
  for(i=0;i<N;i++) printf("%f ",b[i]);
  printf("\n");

  // ベクトル演算 //
  vec_a = _mm256_load_ps(a); //配列aをベクトル演算専用のレジスタへ
  vec_b = _mm256_load_ps(b); //配列bをベクトル演算専用のレジスタへ
  // SIMD（この部分と同じ処理を1年生に分かるように書くならば、  for(i=0;i<N;i++) c[i] = a[i]+b[i]; となる)
  vec_c = _mm256_add_ps(vec_a, vec_b); //c[1:8] = a[1:8] + b[1:8] といったところ
  _mm256_store_ps(c, vec_c);  //答えが入ったベクトル演算専用のレジスタから中身を通常の配列cへ戻す
  // ベクトル演算ここまで //

  //結果表示
  printf("vector C:\n");
  for(i=0;i<N;i++) printf("%f ",c[i]);
  printf("\n");
  printf("[original computation] C:\n");
  for(i=0;i<N;i++) printf("%f ",a[i]+b[i]);
  printf("\n");


  _mm_free(a); // _mm_malloc()に対する、専用のメモリ解放関数
  _mm_free(b);
  _mm_free(c);

  return 0;
}
