/* Lauren Sherman */
/* Parallel version */

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <errno.h>
#include <string.h>
#include "randomStagger.h"

/* Declaration of function to print info to the screen */
void printInfo(int nRow, int nCol, int numExper);

/* Start of main */
int main(int argc, char* argv[])
{
	int nRow;
	int nCol;
	int numExper;

	/*if there are not enough input arguments*/
	if(argc < 4) 
	{
		printf("%s: usage %s inputFile outFile \n", argv[0], argv[0]);
		return 2; 
	}

	/* Set the input values to the numbers of rows, columns, and experiments */
	nRow = (int)(argv[1][0] - '0');
	nCol = (int)(argv[2][0] - '0');
	numExper = (int)(argv[3][0] - '0');

	/* Call the function that will begin to print things to the screen */
	printInfo(nRow, nCol, numExper);

	return 0;
}

/* Function to begin printing info to the screen */
void printInfo(int nRow, int nCol, int numExper)
{
	int i; 
	int seed;
	int status; 
	pid_t pid;
	pid_t childPID;
	int pipeFD[2];
	int numSteps = 0;
	float sumSteps = 0;
	float avgSteps = 0;

	/* Print the numbers of rows, columns, and experiments that the user inputed */
	printf("Floor has %d rows and %d columns, and there are %d experiments\n", nRow, nCol, numExper);

	/* For each experiment, call the randomStagger function and add the number of steps to avgSteps */
	
	/* Linux error handling for pipe() */
	if(pipe(pipeFD) == -1)
	{
		fprintf(stderr, "pipe error: %s \n", strerror(errno));
		exit(-2);
	}

	/* Repeat for each experiment */
	for(i = 0; i < numExper; i++)
	{
		/* Fork */
		pid = fork();

		/* Linux error handling for fork() */
		if (pid < 0)
		{
			fprintf(stderr, "fork error: %s \n", strerror(errno));
			exit(-1);
		}

		/* In each child function, call randomStagger function, print numSteps 
		for that experiment, and pipe numSteps to parent */
		else if(pid == 0)
		{
			close(pipeFD[0]);
			seed = i*10;
			numSteps = randomStagger(nRow, nCol, seed);
			printf("Sailor takes %d steps \n", numSteps);
			write(pipeFD[1], &numSteps, sizeof(numSteps));
			close(pipeFD[1]);
			exit(i);
		}
	}
	
	/* While there are still unwaited-for children */
	while((childPID = wait(&status)) != -1)
	{
		/* Read the value of numSteps from child and add to sumSteps */
		close(pipeFD[1]);
		read(pipeFD[0], &numSteps, sizeof(numSteps));
		sumSteps = sumSteps + numSteps;

		/* If child exits normally, print pid and status */
		if(WIFEXITED(status))
		{
			printf("Child pid %d exited with status %d \n", childPID, WEXITSTATUS(status));
		}
		/* If child does not exit normally, alert user */
		else
		{
			printf("Child %d terminated abnormally \n", childPID);
		}
		fflush(stdout);
	}

	/* Divide the total number of steps by the number of experiments for the average steps */
	avgSteps = sumSteps / numExper;		
	printf("Average number of steps: %f\n", avgSteps);
}
