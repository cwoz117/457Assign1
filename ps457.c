/* * * * * * * * * * * * * * * * * * * * * * * * *
   ps457
   Author: Chris Wozniak
   ID: 10109820

    ps457.c is an extension of the ps command in
linux enviruments, with switches that expand on
additional PID info.
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Switch lookup takes the arguments, and searches them for
//a provided switch. As they can be unordered, we must
//check every location except position 0, which contains
//the function name itself.
int findSwitch(int argLength, char *argp[], char flag){
  int i = 1;
  int found = -1;
  while (i < argLength){
    char *strVal = argp[i];
    if (strlen(strVal) > 1 && strlen(strVal)< 3){
      if(strVal[1] == flag){
	found = i;
	return found;
      }
    } else {
      printf ("Your parameters must be of the form '-x'\n");
      exit(1);
    }
    i++;
  }
  return found;
}

char *buildCommand (char *cmd, char *pid, char *dir, char *file){
  // Create space for the filename
  char *p;
  //+3 for the space, "/" and null terminator
  int size = strlen(cmd) + strlen(dir) +
             strlen(pid) + strlen(dir) + 4;
  p = malloc(size);

  // Concatenate everything together
  strcat(p, cmd);
  strcat(p, " ");
  strcat(p, dir);
  strcat(p, "/");
  strcat(p, pid);
  strcat(p, "/");
  strcat(p, file);
  strcat(p, "\0");

  return p;
}

char *dataIn(char *builtCmd, int i){
  File *pipe;
  pipe = popen(builtCmd, "r");
  if (pipe == NULL){
    printf("Unable to open a pipe");
    exit(1);
  }
  // Parse for the i'th variable here, return it.
  pclose(pipe);
}

int main(int argc, char *argv[]){
  char *path;
  int sw;

  // Single Character State 
  sw = findSwitch(argc, argv, 's');
  if (sw > 0){
    path = buildCommand("", "4429", "stat");
    dataIn(path, 2);
    free(path);
  }

  // User time consumed
  sw = findSwitch(argc, argv, 'U');
  if (sw > 0){
    path = buildCommand("", "4429", "stat");
    dataIn(path, 13);
    free(path);
  }

  // System time consumed
  sw = findSwitch(argc, argv, 'S');
  if (sw > 0){
    path = buildCommand("", "4429", "stat");
    dataIn(path, 14);
    free(path);
  }

  // Virtual Memory consumed
  sw = findSwitch(argc, argv, 'v');
  if (sw > 0){
    path = buildCommand("", "4429", "statm");
    dataIn(path, 0);
    free(path);
  }

  // Command line that started it.
  sw = findSwitch(argc, argv, 'c');
  if (sw > 0){
    path = buildCommand("", "4429", "cmdline");
    dataIn(path, 14);
    free(path);
  }


  
  return 0;
}
