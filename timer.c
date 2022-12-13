/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int alarmOn; 
int num;
int totaltime;
time_t begin;
time_t end; 

void handler(int signum){ 
  //signal handler
  printf("Hello World!\n");
  
  sleep(1);

  alarmOn = 1;
  num++; 

  //exit(1); //exit after printing
}

void sigintHandler(int signum){
  end = time(NULL);
  totaltime = end - begin;

  printf("Total Number Of Alarms: %d Total Seconds: %d\n", num, totaltime);
}

int main(int argc, char * argv[]){
  signal(SIGALRM, handler); //register handler to handle SIGALRM
  signal(SIGINT, sigintHandler); //register handler to handle SIGNIT
  
  //alarm(1); //Schedule a SIGALRM for 1 second

  begin = time(NULL);

  while(1){
    alarmOn = 0;
    alarm(1);

    while(!alarmOn){
      printf("Turing was right!\n");
    }
  } //busy wait for signal to be delivered

  return 0; //never reached
}