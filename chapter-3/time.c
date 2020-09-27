// Return time elapsed to run a process (via shared memory communication)

#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  const int size = sizeof(struct timeval);
  const char *name = "time";
  
  int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  assert(fd != -1);

  ftruncate(fd, size);

  struct timeval *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 

  pid_t pid;
  pid = fork();
  assert(pid != -1);

  if (pid == 0) {
    struct timeval start;
    gettimeofday(&start, NULL);
    *ptr = start;

    execlp(argv[1], argv[1], argv[2], NULL); 
    assert(0);
  }
  else {
    int status;
    wait(&status);
    assert(status != -1);

    struct timeval end;
    gettimeofday(&end, NULL);
    unsigned long long sec = (unsigned int)(end.tv_sec - ptr->tv_sec) * 1000000ULL; 
    unsigned usec = (unsigned int)(end.tv_usec - ptr->tv_usec); 
    printf("%llu\n", + sec + usec);
    return 0;
  }
}
