/* * * * * * * * * * * * * * * * * * * * * * * * *
                      ps457
Author: Chris Wozniak
    ID: 10109820

    ps457.c is an extension of the ps command in
linux enviruments, with switches that expand on
additional PID info.
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdlib.h>

int main(int argc, char *argv[]){
  /* SWITCH CONFIG*/
  // -p <PID> outputs only the requested PID
  // -s look in the STAT dir for single-char state info
  // -U user time consumed (STAT 14th field)
  // -S system time consumed (STAT 15th field) DEFAULT
  // -v virtual memory used (STATM 1st field) DEFAULT
  // -c parent process (cmdline, could be null) DEFAULT
  
  return 0;
}

char[] pidInfo{

  return 'hello';
}
char[] singleCharState(char[] pid){

  return 'hello';
}
char[] userTimeCons(char[] pid){

  return 'hello';
}
char[] sysTimeCons(char[] pid){

  return 'hello';
}
char[] virMemUsed(char[] pid){

  return 'hello';
}
char[] parentProc(char[] pid){

  return 'hello';
}

