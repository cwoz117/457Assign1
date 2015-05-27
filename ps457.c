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
#include "ps457.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                               printOut                                       *
*                                                                              *
*              Takes a character array of output values                        *
*              and prints them to the screen in an ordered                     *
*              stream.                                                         *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void printOut(FILE *fd, char *vals[]){
      int i = 0;
      for (i = 0; i < 6; i++){
            if (vals[i] != NULL){
                  fprintf(fd, "  %s", vals[i]);
                  fprintf(fd, "\t|");
            }
      }

      fprintf(fd, "\n");
}
printHead(FILE *fd, int mask){
      fprintf(fd, "  PID\t");
      if (mask & 16)
            fprintf(fd, "  state\t");
      if (mask & 8)
            fprintf(fd, "  utime\t");
      if (mask & 4)
            fprintf(fd, "  stime\t");
      if (mask & 2)
            fprintf(fd, "  vmem\t");
      if (mask & 1)
            fprintf(fd, "  cmdlne\t|");
      fprintf(fd, "\n");


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
      FILE *output;     // holds all output data.
      char buffer[1024];

      output = fopen (output, "w");
      if (output == NULL){
            printf("Error opening output file!");
            exit(1);
      }

      swMask = findSwitch(argc, argv);
      printHead(output, swMask);

      if (swMask & 32){
            fprintf(fd, findPid(argc, argv));
            if (swMask & 16)
                   fprintf(output, getData(buildPath("/proc", argv[pid], "stat"), 3));
            if (swMask & 8)
                  fprintf(output, getData(buildPath("/proc", argv[pid], "stat"), 14));
            if (swMask & 4)
                  fprintf(output, getData(buildPath("/proc", argv[pid], "stat"), 15));
            if (swMask & 2)
                  fprintf(output, getData(buildPath("/proc", argv[pid], "statm"), 1));
            if (swMask & 1)
                  fprintf(output, getData(buildPath("/proc", argv[pid], "stat"), 1));
            fprintf(output, "\n");

            while (fgets(buffer, 1024, output) != NULL) {
                  printf("%s", buffer);
            }
      } else {
            /*char *pidList;
            int i = 1;
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
            }*/

      }
      return 0;
}
