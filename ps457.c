/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                  ps457                                       *
*                              Chris Wozniak                                   *
*                                10109820                                      *
*                                                                              *
*             ps457.c is an extension of the ps command in                     *
*             linux enviroments, with switches that expand on                  *
*             additional PID info.                                             *
*             -NOTE: "ps457.h" required for the function to run.               *
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
void printOut(char *data[], int len){
	int i = 0;
	while (i < len){
		if (data[i] != NULL){
			printf("%s\t", data[i]);
		}
		i++;
	}
	printf("\n");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                               workSwitch                                     *
*                                                                              *
*             Macro function which parses and conditions output                *
*             depending on whats being called.                                 *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char *workSwitch(char *pid, char *file, int iter){
	char *p;
	char *outVal;

	// get value from current job
	p = buildPath("/proc", pid, file);
	outVal = getData(p, iter);
	free(p);

	p = outVal;
	return p;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                 workPID                                      *
*                                                                              *
*             WorkPID moves through the switches, grabbing                     *
*             specific info for the passed PID value.                          *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int workPID(char *sw[], int argc, char *argv[], char *pid, char *d[], char *h[]){
	int swI;
	int outCount = 1;

	// store PID Info
	h[0] = "PID";
	d[0] = pid;
	outCount = 1;

	// get -s if needed
	swI = findSwitch(argc, &argv[0], &sw[1]);
	if (swI > 0){
		h[1] = "stat";
		d[1] = workSwitch(pid, "stat", 3);
		outCount = 2;
	}

	// get -U (set to 1 for default)
	swI = 1;
	if (swI > 0){
		h[2] = "utime";
		d[2] = workSwitch(pid, "stat", 14);
		outCount = 3;
	}

	// get -S (set to 1 for default)
	swI = 1;
	if (swI > 0){
		h[3] = "stime";
		d[3] = workSwitch(pid, "stat", 15);
		outCount = 4;
	}

	// get -v if needed
	swI = findSwitch(argc, &argv[0], &sw[4]);
	if (swI > 0){
		h[4] = "vmem";
		d[4] = workSwitch(pid, "statm", 1);
		outCount = 5;
	}

	// get -c (set to 1 for default)  ***BUGGED***
	swI = 1;
	if (swI > 0){
		h[5] = "cmdline";
		d[5] = workSwitch(pid, "cmdline", 1);
		outCount = 6;
	}
	return outCount;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                     main                                     *
*                                                                              *
*               checks if we have to look for 1 or many PID's                  *
*               - with -p: get the values and print it.                        *
*               - without: load all PID's into a file,                         *
*                          then parse through them.                            *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main(int argc, char *argv[]){
	char *sw[] = {"-p", "-s","-U", "-S", "-v", "-c"};
	char *dataLine[6] = {'\0'};
	char *header[6] = {'\0'};
	int pid;
	int outCount = 0;

	// Check for -p to determine which route we output.
	pid = findPid(argc, &argv[0], &sw[0]);
	if (pid > 0){
		// BuildHeader(sw, argc, argv);
		outCount = workPID(sw, argc, argv, argv[pid], dataLine, header);

		// Print info
		printOut(&header[0], outCount);
		printOut(&dataLine[0], outCount);
	} else {
		// Get a list of PID's
		system("ps -A -o pid >> tmp.txt");
		FILE *pidList;
		char buffer[128];
		int toggle = 0;

		// Open the list of pid's
		pidList = fopen("tmp.txt", "r");
		if (pidList == NULL){
			printf("Could not get a list of PID's\n");
			exit(1);
		}

		// For each PID, get the PID name, and workPID
		fscanf(pidList, "%s", buffer); // strip off old header
		while (fscanf(pidList, "%s", buffer)!= EOF){
			outCount = workPID(sw, argc, argv, buffer, dataLine, header);
			if (toggle == 0){
				printOut(header, outCount);
				toggle = 1;
			} else {
				printOut(dataLine, outCount);
			}
			// Clear the buffer
			memset(buffer, '\0', 128);
		}
		// Close the file, remove temp file.
		close(pidList);
		system("rm tmp.txt");
	}
	return 0;
}
