#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */


int main(void) {
  char *args[MAX_LINE/2 + 1]; /*command line arguments */
  int should_run = 1; /* flag to determine when to exit program */

    while(should_run){
      printf("osh>");
      fflush(stdout);

      int flag=0;  /*to check the the condition for & */

      /*get command line arguments*/
      char *buf=(char*)malloc(MAX_LINE*sizeof(char));
      ssize_t n = read(0,buf,MAX_LINE);

      if (n==-1){/*error in reading*/
        fprintf(stderr, "error in read funtion");
        return 1;
      }
      /* first argument */
      if(*buf){
        args[0]=buf;
      }
      int i=1;
      while(*buf){
        if(*buf==' '){
          *buf='\0';
          args[i]=(char*)(buf+1);
          i++;
        }
        buf++;
      }
      /* replace '\n with '\0' at last of the input */
      buf--;
      *buf='\0';
      /* terminalte the array of arguments with NULL pointer*/
      args[i]=NULL;

      /* to check exit condition*/
      char pr[80];
      sprintf(pr,args[0],MAX_LINE);
      //printf("%s",pr);
      if(strcmp(pr,"exit")==0){
        should_run=0;
      }

      /* check condition for '&'*/
      i--;
      char new[5];
      sprintf(new,args[i],5);
      if(strcmp(new,"&")==0){
        flag=1;
        printf("%d\n",flag);
        args[i]=NULL;
      }

      pid_t pid;

      /*fork new process*/
      pid=fork();

      if(pid<0){/* error in fork */
        fprintf(stderr, "Fork Failed\n");
        return 1;
      }

      if(pid ==0 ){/* child process */

        /*execute command*/
        execvp(args[0],args);

      }
      if(pid>0){/*parent process*/
        if(flag==0);
          wait(NULL);
      }

    }
  return 0;
}
