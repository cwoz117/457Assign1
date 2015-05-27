/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                                  ps457.h                                     *
*                              Chris Wozniak                                   *
*                                10109820                                      *
*                                                                              *
*             ps457.h contains support functions for the                       *
*             extended ps command as per assignment req's                      *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                               findSwitch                                     *
*                                                                              *
*          Switch lookup take a bitmask, and populates it with                 *
*          identified switches. If it identifies a pid, it                     *
*          gets returned. Otherwise return -1                                  *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int findSwitch(int argLength, char *argp[], int *mask){
	int i = 0;
	int p = -1;
	while (i< argLength){
		if (strcmp(argp[i], "-p")) {
			mask = mask | 1;
			if (arg[i+1] != NULL)
				p = i+1;
		}
		if (strcmp(argp[i], "-s")) {
			mask = mask | 2;
		}
		if (strcmp(argp[i], "-U")) {
			mask = mask | 4;
		}
		if (strcmp(argp[i], "-S")) {
			mask = mask | 8;
		}
		if (strcmp(argp[i], "-v")) {
			mask = mask | 16;
		}
		if (strcmp(argp[i], "-c")) {
			mask = mask | 32;
		}
		i++;
	}
	return p;
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
char *buildPath (char *dir, char *pid, char *file){
  // Create space for the filename
  char *p;

  //+3 for the space, "/" and null terminator
  int size = strlen(dir) +
             strlen(pid) + strlen(file) + 3;
  p = malloc(size);

  // Concatenate everything together
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
*                                 getData                                      *
*                                                                              *
*          Opens the file from the specified file path and extracts            *
*          the i'th value from it.                                             *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char getData(char *filePath, int i){
	int j;				// counter for parsing data stream.
	char *value;			// return value.
	static char buffer[1024];	// buffer for stream.
	char delim[] = " \n\0\t";	// delimeters for string token.
	FILE *data;

	// Open the file, and prep the stream.
	data = fopen(filePath, "r");
	if (data == NULL){
		printf("Unable to read file");
		exit(1);
	}

	// Read the data from the file.
	while (fgets(buffer, 1024, data) != NULL){
		//debug here if req'd
	}

	// Grab the first token, and parse through.
	value = strtok(buffer, delim);
	for (j = 1; j < i; j++){
		value = strtok(NULL, delim);
	}
	fclose(data);
	return value;
}
