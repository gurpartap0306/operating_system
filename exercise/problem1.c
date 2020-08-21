#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  pid_t pid,pid1;

  /* fork a chile process */
  pid = fork();

  if (pid < 0){/* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if(pid == 0){/*child process*/
    //execlp("/bin/ls","ls",NULL);
    //printf("\nhello world");
    pid1=getpid();
    printf("child: pid = %d",pid);
    printf("child: pid1 = %d",pid1);
  }
  else{/*parent process*/
    wait(NULL);
    printf("\nChile Complete");
  }
  return 0;
}
