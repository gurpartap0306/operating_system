/*
  command to compile the program:
  gcc -o consumer consumer.c -pthread -lrt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/mman.h>

int main(int argc, char const *argv[]) {
  /* the size (in bytes) of shared memory object */
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char *name = "OS";
  /* share memory file descriptor*/
  int fd;
  /* pointer to shared memory object */
  char *ptr;

  /*open the shared memory object */
  fd = shm_open(name,O_RDONLY,066);

  /*memory map the shared memory object */
  ptr = (char *)mmap(0,SIZE,PROT_READ, MAP_SHARED,fd,0);

  /*read from the shared memory object */
  printf("%s",(char *)ptr);

  /*remove the shared memory object */
  shm_unlink(name);

  return 0;
}
