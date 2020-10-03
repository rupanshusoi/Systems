#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 100000
#define READ_END 0
#define WRITE_END 1

int main(void)
{
  char string[MAX_LENGTH];
  scanf("%s", string);

  pid_t pid;
  int fd[2];
  assert(pipe(fd) != -1);

  pid = fork();
  assert(pid >= 0);

  if (pid > 0) {
    close(fd[WRITE_END]);

    int status;
    wait(&status);

    int answer;
    read(fd[READ_END], &answer, sizeof(int));
    close(fd[READ_END]);

    if (answer == 1)
      printf("yes\n");
    else
      printf("no\n");
  }
  else { /* child */
    close(fd[READ_END]);

    int is_palindrome = 1;
    for (int i = 0; i < strlen(string); ++i) {
      if (string[i] != string[strlen(string) - 1 - i])
        is_palindrome = 0;
    }

    write(fd[WRITE_END], &is_palindrome, sizeof(int)); 
    close(fd[WRITE_END]);

    exit(0);
  }

  return 0;
}
