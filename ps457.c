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

char *buildCommand (char *cmd, char *pid, char *dir){
  // Create space for the filename
  char *p;
  //+3 for the space, "/" and null terminator
  int size = strlen(cmd) + strlen("/proc/") +
             strlen(pid) + strlen(dir) + 3;
  p = malloc(size);

  // Concatenate everything together
  strcat(p, cmd);
  strcat(p, " ");
  strcat(p,"/proc/");
  strcat(p, pid);
  strcat(p, "/");
  strcat(p, dir);
  strcat(p, "\0");

  return p;
}

int main(int argc, char *argv[]){
  char *path;
  int sw;

  sw = findSwitch(argc, argv, 's');
  if (sw > 0){
    path = buildCommand("cat", "2050", "stat");
    system(path);
  }

  free(path);
  return 0;
}
