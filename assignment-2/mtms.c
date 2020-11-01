#include <stdio.h>
#include <pthread.h>

struct merge_data {
  int lo, hi;
  int* arr;
};

void merge(int* arr, int lo, int mid, int hi) {
  int p = mid - lo + 1;
  int q = hi - mid;

  int L[p], R[q];
  for(int i = 0; i < p; i++)
      L[i] = arr[lo + i];
  for(int j = 0; j < q; j++)
      R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = lo;
   
  while (i < p && j < q) {
    if (L[i] <= R[j])
      arr[k] = L[i++];
    else
      arr[k] = R[j++];
    k++;
  }

  while (i < p) { 
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < q) {
      arr[k] = R[j];
      j++;
      k++;
  }
}
 
void* merge_sort(void* param) {
  struct merge_data* data = (struct merge_data*)param;

  int lo = data->lo;
  int hi = data->hi;

  if (lo < hi) {
    int mid = (lo + hi) / 2;
  
    pthread_t lo_id, hi_id;
    pthread_attr_t attr;
  
    pthread_attr_init(&attr);
  
    int* arr = data->arr;

    struct merge_data lo_data = {lo, mid, arr};
    struct merge_data hi_data = {mid + 1, hi, arr};
  
    pthread_create(&lo_id, &attr, merge_sort, &lo_data);
    pthread_create(&hi_id, &attr, merge_sort, &hi_data);
  
    pthread_join(lo_id, NULL);
    pthread_join(hi_id, NULL);
  
    merge(arr, lo, mid, hi);
  }
}

int main() {
  
  int N;
  scanf("%d", &N);

  int arr[N];
  for (int i = 0; i < N; ++i) {
    scanf("%d", &arr[i]);
  }

  struct merge_data data = {0, N - 1, arr};

  merge_sort(&data);

  for (int i = 0; i < N; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}
