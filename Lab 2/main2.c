#include  <stdio.h>
#include  <sys/types.h>
#include  <unistd.h>
#include  <stdlib.h>
#include  <sys/wait.h>
#include  <time.h>

#define   MAX_COUNT  200

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

int  main(void)  //change type to return a value 
{
     pid_t  pid;
     int i; 

     for(i = 0; i < 2; i++){
      pid = fork();
      if (pid == 0){
       ChildProcess();
      }

      else{
       ParentProcess();
      }
     }
    return 0;
}

void  ChildProcess(void)
{
     int   i;
     int num;

     printf("Child Pid: %d is going to sleep!\n", getpid());

     srand(getpid());
     num = rand() % 11; // generates random number between 1 - 10
     sleep(num);

     printf("Child Pid: is awake!\nWhere is my Parent: %d ?\n", getpid());

     exit(0);

    /* for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     printf("   *** Child process is done ***\n"); */
}

void  ParentProcess(void)
{
     int   i;
     int pid; 
     int status; 

     for(i = 1; i < 2; i++){
       pid = wait(&status);
       printf("Child Pid: %d has completed\n", getpid());
     }

     /* for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     printf("*** Parent is done ***\n"); */
}