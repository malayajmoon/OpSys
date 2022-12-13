/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int alarmOn; 

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  //exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM, handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second

  while(1){
    alarmOn = 0;
    alarm(1);

    while(!alarmOn){
      printf("Turing was right!\n");
    }
  } //busy wait for signal to be delivered

  return 0; //never reached
}