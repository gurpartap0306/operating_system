#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <sys/time.h>

long long int stringToint(char *);

int main(int argc, char const *argv[]) {
  char path[30];
  pid_t pid;
  /* size(in bytes) of shared memory object*/
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char *name ="OS";

  /* shared memory file descriptor */
  int fd;
  /* pointer to shared memory object*/
  char *ptr;

  pid = fork();

  if (pid<0){
    fprintf(stderr, "Fork Failed\n");
    return 1;
  }

  if (pid == 0){/* child process*/
    /*structure to store time stamp*/
    struct timeval current;
    gettimeofday(&current,NULL);

    /*create the shared memory object*/
    fd = shm_open(name,O_CREAT | O_RDWR,0666);
    /*configure the size of shared memory object*/
    ftruncate(fd,SIZE);
    /* memory map the shared memory object*/
    ptr=(char*)mmap(0,SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);

    /*write to shared memory object*/
    sprintf(ptr,"%ld",current.tv_sec);
    ptr+=sizeof(current.tv_sec);
    //sprintf(ptr,"%s","and");
    //ptr+=strlen("and");
    sprintf(ptr,"%ld",current.tv_usec);
    ptr+=sizeof(current.tv_usec);

    //char path[15];
    char *p=path;
    sprintf(p,"/bin/%s",argv[1]);
    execlp(path,argv[1],NULL);
    //execv(path,argv[1]);

  }

  if (pid>0){
    wait(NULL);
    /*open the shared memory object*/
    fd = shm_open(name,O_RDONLY,0666);
    /*memory map the shared memory object*/
    ptr = (char*)mmap(0,SIZE,PROT_READ,MAP_SHARED,fd,0);

    long long int t2=stringToint((char*)ptr);

    char buff[SIZE];
    char *ptr1=buff;
    /*structure for tme stamp*/
    struct timeval current;
    gettimeofday(&current,NULL);

    sprintf(ptr1,"%ld",current.tv_sec);
    ptr1+=sizeof(current.tv_sec);
    sprintf(ptr1,"%ld",current.tv_usec);
    ptr1=buff;
    long long int t1=stringToint(ptr1);

    /* escape time*/
    printf("escapr time: %lli\n",t1-t2);
    /*unlink and delet the memory object*/
    shm_unlink(name);
  }

  return 0;
}

long long int stringToint(char *ptr){
  long long int r=0;
  while(*ptr!='\0'){
    r=10*r+(*ptr)-'0';
    ptr++;
  }
  return r;
}
