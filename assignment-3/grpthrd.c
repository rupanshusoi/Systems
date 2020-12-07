#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#define MAX_INPUT_LINES 100
#define MAX_LINE_LENGTH 100
#define MAX_TESTS 100

char input[MAX_INPUT_LINES][MAX_LINE_LENGTH];
int output[MAX_TESTS][MAX_INPUT_LINES];
char tests[MAX_TESTS][MAX_LINE_LENGTH];

int N, T;

void* grep(void* param) {
  int idx = *(int*)param;

  for (int i = 0; i < N; ++i) {
    if (strcasestr(input[i], tests[idx])) {
      output[idx][i] = 1;
    }
  }

  return NULL;
}

int main() {
  scanf("%d\n", &N);
  assert(N <= MAX_INPUT_LINES);

  char c;

  for (int i = 0; i < N; ++i) {
    int j = 0;
    while ((c = getchar()) != '\n') {
      input[i][j++] = c;
    }
    input[i][j] = '\0';
  }

  scanf("%d\n", &T);
  assert(T <= MAX_TESTS);

  for (int i = 0; i < T; ++i) {
    int j = 0;
    while ((c = getchar()) != '\n') {
      tests[i][j++] = c;
    }
    tests[i][j] = '\0';
  }

  for (int i = 0; i < T; ++i) {
    for (int j = 0; j < N; ++j) {
      output[i][j] = 0;
    }
  }

  pthread_t threads[T];

  pthread_attr_t attr;
  pthread_attr_init(&attr);

  int indices[T];
  for (int i = 0; i < T; ++i) {
    indices[i] = i;
    pthread_create(&threads[i], &attr, grep, &indices[i]);
  }

  for (int i = 0; i < T; ++i) {
    pthread_join(threads[i], NULL);
  }

  for (int i = 0; i < T; ++i) {
    for (int j = 0; j < N; ++j) {
      if (output[i][j]) {
        puts(input[j]);
      }
    }
  }
  return 0;
}

