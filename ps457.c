/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                  ps457                                       *
*                              Chris Wozniak                                   *
*                                10109820                                      *
*                                                                              *
*             ps457.c is an extension of the ps command in                     *
*             linux enviroments, with switches that expand on                  *
*             additional PID info.                                             *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include ps457.h

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
    if (vals[i] != NULL){
      printf("  %s", vals[i]);
      printf("\t|");
    }
  }

  printf("\n");

}
void printHead(){
      printf("  PID\t");
      if (vals[1] != NULL)
        printf("  state\t");
      if (vals[2] != NULL)
        printf("  utime\t");
      if (vals[3] != NULL)
        printf("  stime\t");
      if (vals[4] != NULL)
        printf("  vmem\t");
      if (vals[5] != NULL)
        printf("  cmdlne\t|");
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
      int swMask = 0;   // bitmask where each bit represents a switch
      int p;            // points to where the pid is in argv.
      char *output[6];

      p = findSwitch(argc, argv, &swMask);
      if (swMask & 32){
            output[0] = argv[pid];
            if (swMask & 16)
                  output[1] = getData(buildPath("/proc", argv[pid], "stat"), 3);
            if (swMask & 8)
                  output[2] = getData(buildPath("/proc", argv[pid], "stat"), 14);
            if (swMask & 4)
                  output[3] = getData(buildPath("/proc", argv[pid], "stat"), 15);
            if (swMask & 2)
                  output[4] = getData(buildPath("/proc", argv[pid], "statm"), 1);
            if (swMask & 1)
                  output[5] = getData(buildPath("/proc", argv[pid], "stat"), 1);
            printHead();
            printOut(output);
      } else {
            char *pidList;
            int i = 1;
            printHead();
            while ((pidList = getData("ls /proc"), i) != NULL) {
                  output[0] = pidList;
                  if (swMask & 16)
                        output[1] = getData(buildPath("/proc", pidList, "stat"), 3);
                  if (swMask & 8)
                        output[2] = getData(buildPath("/proc", pidList, "stat"), 14);
                  if (swMask & 4)
                        output[3] = getData(buildPath("/proc", pidList, "stat"), 15);
                  if (swMask & 2)
                        output[4] = getData(buildPath("/proc", pidList, "statm"), 1);
                  if (swMask & 1)
                        output[5] = getData(buildPath("/proc", pidList, "stat"), 1);
                  printOut(output);
                  i++;
            }

      }
      return 0;
}
