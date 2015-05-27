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
int findSwitch(int argLength, char *argp[]){
	int i = 0;
	int p = -1;
	int msk = 0;

	while (i< argLength){
		if (strcmp(argp[i], "-p")) {
			msk = msk | 1;
		}
		if (strcmp(argp[i], "-s")) {
			msk = msk | 2;
		}
		if (strcmp(argp[i], "-U")) {
			msk = msk | 4;
		}
		if (strcmp(argp[i], "-S")) {
			msk = msk | 8;
		}
		if (strcmp(argp[i], "-v")) {
			msk = msk | 16;
		}
		if (strcmp(argp[i], "-c")) {
			msk = msk | 32;
		}
		i++;
	}
	return msk;
}

char *findPid(int ac, char *av){
	int i;
	for (i = 0; i < ac; i++){
		if (strcmp(av[i], "-p")){
			if (av[i+1] == NULL){
				printf("error in args");
				exit(1);
			} else {
				return av[i+1];
			}
		}
	}
	return -1;
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
