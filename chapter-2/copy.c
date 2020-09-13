#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main(int argc, char* argv[]) {
  int src = open(argv[1], O_RDONLY);
  if (src == -1) {
    perror("Could not open source file");
    return 8;
  }

  int dest = open(argv[2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
  if (dest == -1) {
    perror("Could not create destination file");
    return 8;
  }

  int buffer[BUF_SIZE];
  int bytes_read, bytes_written;
  while ((bytes_read = read(src, buffer, BUF_SIZE)) > 0) {
    bytes_written = write(dest, buffer, bytes_read);
    if (bytes_written == -1) {
      perror("Could not write to file");
      return 8;
    }
    else if (bytes_written != bytes_read) {
      perror("Bytes written not equal to bytes read");
      return 8;
    }
  }  
  if (bytes_read == -1) {
    perror("Could not read file");
    return 8;
  }

  close(src);
  close(dest);

  return 0;
}
