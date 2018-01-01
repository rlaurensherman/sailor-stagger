/* Lauren Sherman */
/* Sequential version */

#include <stdio.h> 
#include <stdlib.h>
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
	int numSteps;
	int i; 
	int seed;
	float avgSteps = 0;

	/* Print the numbers of rows, columns, and experiments that the user inputed */
	printf("Floor has %d rows and %d columns, and there are %d experiments\n", nRow, nCol, numExper);

	/* For each experiment, call the randomStagger function and add the number of steps to avgSteps */
	for(i = 0; i < numExper; i++)
	{
		seed = i*10;
		numSteps = randomStagger(nRow, nCol, seed);
		printf("Sailor takes %d steps \n", numSteps);
		avgSteps = avgSteps + numSteps;
	}
	/* Divide avgSteps (which is now the total steps) by the number of experiments */
	avgSteps = avgSteps / numExper;
	printf("Average number of steps: %f\n", avgSteps);
}
