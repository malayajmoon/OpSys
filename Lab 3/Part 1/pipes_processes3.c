#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Executes the command "cat scores | grep Lakers".  In this quick-and-dirty
 * implementation the parent doesn't wait for the child to finish and
 * so the command prompt may reappear before the child terminates.
 *
 */

int main(int argc, char **argv)
{
  int pipefd1[2];
  int pipefd2[2];
  int pid1;
  int pid2;
  int pid3; 
   

  char *cat_args[] = {"cat", "scores", NULL}; // P1 cat scores 
  char *grep_args[] = {"grep", "Lakers", NULL}; //P2 grep <argument>
  char *sort_args[] = {"sort",NULL, NULL}; //P2 Child sort 

  // make a pipe (fds go in pipefd[0] and pipefd[1])

  pipe(pipefd1);
  pipe(pipefd2);

  pid2 = fork();

  if (pid2 == 0)
    {
      // child gets here and handles "grep Villanova"

      // replace standard input with input part of pipe

      dup2(pipefd1[1], 1);

      // close unused half of pipe

      close(pipefd1[1]);
      close(pipefd1[0]);
      close(pipefd2[1]);
      close(pipefd2[0]);

      // execute grep

      execvp(*grep_args, grep_args);
    }

      // parent gets here and handles "cat scores"

      // replace standard output with output part of pipe

  pid1 = fork();

  if(pid1 == 0){

    dup2(pipefd1[0], 0);
    dup2(pipefd2[1], 1);

    // close unused half of pipe

    close(pipefd1[1]);
    close(pipefd1[0]);
    close(pipefd2[1]);
    close(pipefd2[0]);

    // execute cat

    execvp(*cat_args, cat_args);
  }

  //Child's Child execute sort 

pid3 = fork(); 

if(pid3 == 0){


  dup2(pipefd1[0], 0);

  //close unused half of pipe 

  close(pipefd1[1]);
  close(pipefd1[0]);
  close(pipefd2[0]);
  close(pipefd2[1]);

  //execute sort 

  execvp(*sort_args, sort_args); 
}

wait(NULL);
  return; 
}