//配列 の平方根および、逆数を求める
#include <stdio.h>
#include <math.h>
#include <immintrin.h>

#define N 24

int main(){
  int i;
  int num_chunk, vec_size = sizeof(__m256)/sizeof(float);
  double st,et;

  float *a,*b,*c, *c_orig;
  __m256 vec_a,vec_b,vec_c;


  a = (float *)_mm_malloc(sizeof(float)*N,32);
  b = (float *)_mm_malloc(sizeof(float)*N,32);
  c = (float *)_mm_malloc(sizeof(float)*N,32);
  for(i=0;i<N;i++){
    a[i] = (float)i*1.0;
  }

  printf("vector A:\n");
  for(i=0;i<N;i++) printf("%f ",a[i]);
  printf("\n");

  num_chunk = N/vec_size;

  for(i=0;i<num_chunk;i++){
    vec_a = _mm256_load_ps(a+vec_size*i);  //float型の配列a[] からvec_aに取り出す
    vec_b = _mm256_sqrt_ps(vec_a);     //vec_b はvec_aの平方根を入れる
    vec_c = _mm256_rcp_ps(vec_a);      //vec_c はvec_aの逆数を入れる
      
    _mm256_store_ps(b+vec_size*i, vec_b);//vec_bの答え（a[]の平方根）をfloat型の配列b[]に戻す
    _mm256_store_ps(c+vec_size*i, vec_c);//vec_cの答え（a[]の逆数）をfloat型の配列c[]に戻す
  }
  
  
  
  printf("square root of a[]:\n");
  for(i=0;i<N;i++) printf("%f ",b[i]);
  printf("\n");

  printf("reciprocal number of a[]:\n");
  for(i=0;i<N;i++) printf("%f ",c[i]);
  printf("\n");

  _mm_free(a);
  _mm_free(b);
  _mm_free(c);

  return 0;
}
