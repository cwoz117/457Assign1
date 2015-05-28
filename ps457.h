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
*          parses the argv array for the provided switch, and returns          *
*          the position where the switch was found.                            *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int findSwitch(int argLength, char *argp[], char *f[]){
	int found = -1;
	int i = 1;
	char *p;
	while (i < argLength){
		p = strstr(argp[i], f[0]);
		if (p != NULL){
			found = i;
		}
		i++;
	}
	return found;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                              *
*                               findPid                                        *
*                                                                              *
*                                                                              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int findPid(int ac, char *av[], char *f[]){
	int i = 1;
	char *p;
	while (i < ac){
		p = strstr(av[i], f[0]); //pg.116 ANSI C
		if (p != NULL){
			if (av[i+1] == NULL){
				printf("error in args");
				exit(1);
			} else {

				return i+1;
			}
		} else {

		}
		i++;
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
	p = calloc(sizeof(p), size);

	 // Concatenate everything together
	strcat(p, dir);
	if (pid != "")
		strcat(p, "/");
	strcat(p, pid);
	if (file != "")
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
char *getData(char *filePath, int i){
	int j = 0;				// counter for parsing data stream.
	char *value;			// return value.
	char buffer[128];	// buffer for stream.
	char *buf;
	char delim[] = " \n\0\t";	// delimeters for string token.
	FILE *data;

	// Open the file, and prep the stream.
	data = fopen(filePath, "r");
	if (data == NULL){
		printf("could not open file %s\n", filePath);
		exit(1);
	}

	// Read the data from the file.
	while (j < i){
		memset(buffer, '\0', 128);
		fscanf(data, "%s", buffer);
		j++;
	}

	buf = (char*) malloc(sizeof(buffer));
	strcpy(buf, buffer);
	fclose(data);

	return buf;
}
