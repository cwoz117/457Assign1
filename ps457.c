/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                  ps457                                       *
*                              Chris Wozniak                                   *
*                                10109820                                      *
*                                                                              *
*             ps457.c is an extension of the ps command in                     *
*             linux enviruments, with switches that expand on                  *
*             additional PID info.                                             *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                               findSwitch                                     *
*                                                                              *
*          Switch lookup takes provided args, and searches them for            *
*          against a switch. As they can be unordered, we must                 *
*          check every location (except position 0, which contains             *
*          the function name itself.)                                          *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                               buildCommand                                   *
*                                                                              *
*          buildCommand takes the multiple substrings needed for               *
*          the program to run. It takes the substrings and                     *
*          concatenates them together, allocating the memory to                *
*          make them fit.                                                      *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char *buildCommand (char *cmd, char *dir, char *pid, char *file){
  // Create space for the filename
  char *p;

  //+3 for the space, "/" and null terminator
  int size = strlen(cmd) + strlen(dir) +
             strlen(pid) + strlen(file) + 4;
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                runCmd                                        *
*                                                                              *
*             runCmd takes the built command, and a counter to                 *
*             open a pipe, and execute the command. Once we have               *
*             the output, we then return the information at the                *
*             i'th position                                                    *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char *runCmd(char *strCmd, int i){
  const int MAX_BUF = 512;
  const char s[1] = " ";
  int j = 0;
  char *value;
  char buffer[MAX_BUF];
  FILE *pipe;

  pipe = popen(strCmd, "r");
  if (pipe == NULL){
    printf("Unable to open a pipe");
    exit(1);
  }
  
  fgets(buffer, MAX_BUF, pipe);
  value = strtok(buffer, s);
  while (j <= i){
    value = strtok(NULL, s);
    j ++;
  }
 
  pclose(pipe);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                  main                                        *
*                                                                              *
*                                                                              *
*                                                                              *
*                                                                              *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main(int argc, char *argv[]){
  int i;
  char *output[6] = '\0';
  char *path;
  int sw;

  output[0] = "2257";
  
  // Single Character State
  sw = findSwitch(argc, argv, 's');
  if (sw > 0){
    path = buildCommand("cat", "/proc", "2257", "stat");
    output[1] = runCmd(path, 2);
    
    free(path);
  }

  for (i = 0; i < 6; i++){
    if (output[i] != NULL){
      printf("%s", output[i]);
    }
  }
  /*
  // User time consumed
  sw = findSwitch(argc, argv, 'U');
  if (sw > 0){
    path = buildCommand("", "4429", "stat");
    runCmd(path, 13);
    free(path);
  }

  // System time consumed
  sw = findSwitch(argc, argv, 'S');
  if (sw > 0){
    path = buildCommand("", "4429", "stat");
    runCmd(path, 14);
    free(path);
  }

  // Virtual Memory consumed
  sw = findSwitch(argc, argv, 'v');
  if (sw > 0){
    path = buildCommand("", "4429", "statm");
    runCmd(path, 0);
    free(path);
  }

  // Command line that started it.
  sw = findSwitch(argc, argv, 'c');
  if (sw > 0){
    path = buildCommand("", "4429", "cmdline");
    runCmd(path, 14);
    free(path);
  }


*/
  return 0;
}
