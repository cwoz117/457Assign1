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
  const int MAX_BUF = 1024;
  const char s[1] = " ";
  int j = 1;
  char *value;
  char buffer[MAX_BUF];
  FILE *pipe;

  pipe = popen(strCmd, "r");
  if (pipe == NULL){
    printf("Unable to open a pipe");
    exit(1);
  }
  
  while(fgets(buffer, MAX_BUF, pipe)!= NULL){

  }

  value = strtok(buffer, s);
  while (j <= i){
    // printf("%s\n", value);
    value = strtok(NULL, s);
    j ++;
  }
  pclose(pipe);
  return value;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                               printOut                                       *
*                                                                              *
*              Takes a character array of output values                        *
*              and prints them to the screen in an ordered                     *
*              stream.                                                         *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void printOut(char *vals[]){

  int i = 0;
  
  for (i = 0; i < 6; i++){
    if (vals[i] != '\0'){
      printf("%s\t", vals[i]);
    }
  }

  printf("\n");

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
  char *output[6] = {'\0'};
  char pid[5] = "565\0";
  char *path;
  int sw;


  output[0] = pid;

  // Single Character State
  sw = findSwitch(argc, argv, 's');
  if (sw > 0){
    path = buildCommand("cat", "/proc", pid, "stat");
    output[1] = runCmd(path,2);
    free(path);
  }

  // User time consumed
  sw = 1; // Defaults to be true.
  if (sw > 0){
    path = buildCommand("cat", "/proc", pid, "stat");
    output[2] = runCmd(path, 13);
    free(path);
  }
  // System time consumed
  sw = 1; // Defaults to be true.
  if (sw > 0){
    path = buildCommand("cat", "/proc", pid, "stat");
    output[3] = runCmd(path, 14);
    free(path);
  }
  
  // Virtual Memory consumed
  sw = findSwitch(argc, argv, 'v');
  if (sw > 0){
    path = buildCommand("cat", "/proc", pid, "statm");
    output[4] =runCmd(path, 0);
    free(path);
  }
  /*
  // Command line that started it.
  sw = findSwitch(argc, argv, 'c');
  if (sw > 0){
    path = buildCommand("", "/proc", pid, "cmdline");
    output[5] =runCmd(path, 14);
    free(path);
  }


*/
  printOut(output);
  return 0;
}
