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
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
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
*/
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

      int *swMsk[6] = {0};
	char *pid;
	
      	findSwitch(argc, &argv, &swMsk);

	if (swMsk[0] == 1){
		pid = findPid(argc, &argv[0]);
		printf("%s\n", pid);
	}










      return 0;

}
