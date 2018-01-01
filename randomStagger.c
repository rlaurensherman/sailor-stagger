/* Lauren Sherman */
/* Random stagger function source file */

#include <stdlib.h>
#include "randomStagger.h"

/* Function to simulate one entire experiment of random staggering */
int randomStagger(int nRow, int nCol, int seed)
{
	int numSteps = 0;
	int rMove = 0; /* Distance sailor will move in the row */
	int cMove = 0; /* Distance sailor will move in the column */
	int rowPosition = (nRow/2); /* Sailor's row position in middle of board */
	int colPosition = (nCol/2); /* Sailor's column position in middle of board */
	srand(seed);

	/* While the sailor is not out of bounds */
	while((colPosition >= 0)&&(colPosition < nCol)&&(rowPosition >= 0)&&rowPosition < nRow)
	{
		rMove = (rand()%3) - 1;
		cMove = (rand()%3) - 1;
		
		/* If rMove and cMove are both 0, do not increment number of steps */
		if((rMove==0)&&(cMove==0))
		{
			continue;
		}
		/* Otherwise, move the row and column positions and increment the number of steps */
		else
		{
			rowPosition = rowPosition + rMove;
			colPosition = colPosition + cMove;
			numSteps++;
		}
	}
	/* Return the number of steps */
	return numSteps;
}
