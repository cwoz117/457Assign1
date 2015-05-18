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
  int found = 0;
  while (i < argLength){
    char chArg[strlen(argp[i])];
    strcpy(chArg, argp[i]);
    if (chArg[0] == '-'){
      if (chArg[1] == flag)
	found  = 1;
    }
    i++;
  }
  return found;
}

int main(int argc, char *argv[]){
  printf("hello \n");
  int c = findSwitch(argc, &argv, 'c');
  if (c == 1)
      printf("found c");
  /* SWITCH CONFIG*/
  // -p <PID> outputs only the requested PID
  // -s look in the STAT dir for single-char state info
  // -U user time consumed (STAT 14th field)
  // -S system time consumed (STAT 15th field) DEFAULT
  // -v virtual memory used (STATM 1st field) DEFAULT
  // -c parent process (cmdline, could be null) DEFAULT
  
  return 0;
}
/*
&char[] pidInfo(){

  return 'hello';
}
&char[] singleCharState(char[] pid){

  return 'hello';
}
&char[] userTimeCons(char[] pid){

  return 'hello';
}
&char[] sysTimeCons(char[] pid){

  return 'hello';
}
&char[] virMemUsed(char[] pid){

  return 'hello';
}
&char[] parentProc(char[] pid){

  return 'hello';
}
*/
