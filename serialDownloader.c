//Pooja Srivatava
//Tony Pham
//CPSC 351
//Assignment #1
//Serial Downloader

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	FILE *fp;					//File pointer
	char url[10][200];			//Array used to store each url from file
	int n = 0;					//Counter variable
	int c;						//Holds the index to access urls in the array
	
	fp = fopen("urls.txt", "r");
	
	//Error check to see if file was opened correctly
	if (fp == NULL)
	{
		fprintf(stderr, "Cannot open file urls.txt! \n");
		exit(1);
	}
	//Get the line(url) count from the file and store the lines in the array
	do {
		c = fgetc(fp);
		if (c == '\n'){
			n++;}
	} while (c != EOF);
	
	//Set file pointer back to the start of the file
	rewind(fp);
	printf("Number of lines in file: %i\n", n);
	
	//Iterate through all urls in the file
	for (c = 0; c < n; ++c)
	{
		fscanf(fp, "%s", url[c]);
		if (url[c][0] == 'h' && url[c][1] == 't') {
			pid_t pid[c];
			pid[c] = fork();
			if (pid[c] < 0) {
				printf("Fork Failed\n");
				exit(-1);
			}
			else if (pid[c] == 0)  {
				execlp("/usr/bin/wget", "wget", url[c], NULL);
			}
			else {
				wait (NULL);
				printf("Child Complete\n");
			}
		}
	}

	fclose(fp);
}
