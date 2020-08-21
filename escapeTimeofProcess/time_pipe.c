#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/wait.h>

#include <sys/time.h>

#define BUFFER_SIZE 30
#define READ_END 0
#define WRITE_END 1

long long int stringToint(char *);

int main(int argc, char const *argv[]) {
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;

  /*create the pipe*/
  if(pipe(fd)==-1){
    fprintf(stderr, "Pipe failed");
    return 1;
  }
  /*fork a child process*/
  pid = fork();

  if(pid <0){/*error occured*/
    fprintf(stderr, "Fork Failed");
    return 1;
  }

  if(pid==0){/*child process*/
    /*close the unused end of pipe*/
    close(fd[READ_END]);

    /* store path in a buf*/
    char buf[15];
    char *ptr1=buf;
    sprintf(ptr1,"/bin/%s",argv[1]);

    /*structure for time stamp*/
    struct timeval current;
    gettimeofday(&current,NULL);

    /*write time into buffer*/
    char write_msg[BUFFER_SIZE];
    char *ptr=write_msg;
    sprintf(ptr,"%ld",current.tv_sec);
    ptr+=sizeof(current.tv_sec);
    sprintf(ptr,"%ld",current.tv_usec);
    ptr+=sizeof(current.tv_usec);

    /*write to the pipe*/
    write(fd[WRITE_END],write_msg,strlen(write_msg)+1);

    /*close the write end of pipe*/
    close(fd[WRITE_END]);

    /*execute the command*/
    execlp(buf,argv[1],NULL);
  }
  if(pid>0){
    wait(NULL);

    /*close the unused end of pipe*/
    close(fd[WRITE_END]);

    /*read from the pipe*/
    read(fd[READ_END],read_msg,BUFFER_SIZE);

    long long int t1=stringToint(read_msg);

    /* structure for time stamp*/
    struct timeval current ;
    gettimeofday(&current,NULL);

    /*store time stap in buf*/
    char buf[BUFFER_SIZE];
    char *ptr=buf;
    sprintf(ptr,"%ld",current.tv_sec);
    ptr+=sizeof(current.tv_sec);
    sprintf(ptr,"%ld",current.tv_usec);

    long long int t2=stringToint(buf);

    printf("escape time: %lld\n",t2-t1);

    /*read read end of pipe*/
    close(fd[READ_END]);

  }

  return 0;
}

long long int stringToint(char *ptr){
  long long int r=0;
  while(*ptr!='\0'){
    r=r*10+(*ptr)-'0';
    ptr++;
  }
  return r;
}
