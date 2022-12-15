#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[256] = "> ";
char delimiters[] = " \t\r\n";
extern char **environ;
pid_t pid;
int status;
int i;  



int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    	
    while (true) {
      
        do{ 

            // 0. Modify prompt

            if(getcwd(prompt, sizeof(prompt)) != NULL){
              // Print the shell prompt
              printf("%s", prompt);
              fflush(stdout);
            }

            // Read input from stdin and store it in command_line. If there's an
            // error, exit immediately. (If you want to learn more about this line,
            // you can Google "man fgets")
        
            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
            }
 
        }
        
        while(command_line[0] == 0x0A);  // while just ENTER pressed

      
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 
        
			  // 0. Modify the prompt to print the current working directory
        // code above 
			  
			
        // 1. Tokenize the command line input (split it on whitespace)

        arguments[0] = strtok(command_line, delimiters);

        i = 0; 

        while(arguments[i] != NULL){
          i++; 
          arguments[i] =strtok(NULL, delimiters);
        }

      
        // 2. Implement Built-In Commands

        if(strcmp(arguments[0], "cd") == 0){
          chdir(arguments[1]); //changes current working direcotry 
        }

        else if(strcmp(arguments[0], "pwd") == 0){
          printf("%s\n", prompt); //prints current working directory 
        }

        else if(strcmp(arguments[0], "echo") == 0){ //prints message and values of environment variables
          i = 0; 
          while(arguments[i] != NULL){
            if (*arguments[i] == '$'){
              if(getenv(agruments[i] + 1) != NULL){
                printf("%s\n", getenv(arguments[i] +1)); 
              }
            }
            else{
              printf("%s ", arguments[i]);
            }

            i++;
          }
        }

        else if(strcmp(arguments[0], "exit") == 0){
          exit(0); // terminates shell 
        }

        else if(strcmp(arguments[0], "evn") == 0){ // prints current values of environment variables
          i = 1; 

          if(arguments[i] != NULL){
            if(getenv(arguments[i]) != NULL){
              printf("%s\n", getenv(arguments[i]));
            }
          }

          else if(arguments[i] == NULL){
            while(environ[i] != NULL){
              printf("%s\n", getenv(environ[i]));
              i++;
            }
          }
        }

        else if(strcmp(arguments[0], "setenv") == 0){ //sets environment variable
          if(arguments[1] != NULL && arguments[2] != NULL){
            setenv(arguments[1], arguments[2], 1); 
          }
        }
    
        // 3. Create a child process which will execute the command line input
        // 4. The parent process should wait for the child to complete unless its a background process

        else{
          pid = fork();
          i = 0;  

          if(pid == 0){ // child process excuting command line input 
            execvp(arguments[i], arguments);
          }

          else if(pid < 0){ //failure -> program terminates 
            printf("error: failure occured for requested process\n");
            exit(1);
          }

          else{ // parent process, wait for child process to complete 
            wait(&status); 
          }
        }
      
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}