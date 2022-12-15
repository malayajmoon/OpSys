#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <unistd.h>
#include  <sys/wait.h>
#include  <semaphore.h>
#include  <sys/stat.h>
#include  <fcnt1.h>
#include  <sys/mman.h>



//void PoorStudent(int []);
//void DearOldDad(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;
     sem_t *mutex;

     if ((mutex = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED){
      perror("semaphore initilization");
      exit(1);
   }

     ShmID = shmget(IPC_PRIVATE, 2*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
    
     int BankAccount = 0; 
     //int Turn = 0;
     //int Deposit = 0; 
     ShmPTR[0] = BankAccount; 
     //ShmPTR[1] = Turn; 

     printf("The Initial Balance: $ %d\n", ShmPTR[0]);
     
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
        }
        else if (pid == 0) {
          PoorStudent(ShmPTR, mutex);
          exit(0);
        }
        else{
          DearOldDad(ShmPTR, mutex); 
        }
        wait(&status);
        
        return 0; 
}

void DearOldDad(int *SharedMem){ //parent process 
  unsigned int i; 
  signed int account;
  signed int deposit; 
  srand(getpid());

  for(i = 0; i < 25; i++){
    sleep(rand() % 6);
    sem_wait(mutex);
    account = *SharedMem;

    /*while(SharedMem[1] != 1){
      ;
    } */
  } 

  if (account <= 100){
    deposit = rand() % 101;
    if(deposit % 2 == 0){
      account = account + deposit;
      printf("Dear old Dad: Deposits $%d / Balance = $%d\n", deposit, account);
    }
    else{
      printf("Dear old Dad: Doesn't have any money to give\n");
    }

    *SharedMem = account;
  }
  else{
    printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account);
  }

  sem_post(mutex); 
}


void PoorStudent(int *SharedMem){
  unsigned int i; 
  signed int balance; 
  signed int account; 
  srand(getpid());

  for(i = 0; i < 25; i++){
    sleep(rand() % 6);
    sem_wait(mutex);
    account = *SharedMem;

    
    /* while(SharedMem[1] != 1){
      ;
    } */
    
    balance = rand() % 51;
    printf("Poor Student needs $%d\n", balance);

    if (balance <= account){
      account = account - balance;

      printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, account);
      *SharedMem = account;
    }
    else if(balance > account){
      printf("Poor Student: Not Enough Cash ($%d)\n", account);
    }

    sem_post(mutex);
  }
    //SharedMem[0] = account; 
    //SharedMem[1] = 0; 
}