#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*Introduction Paragraph:
 *This program solves a maze by determining where in the maze the program can
 *move to reach the end of the maze. The createMaze function allocates Memory
 *for the board and cells. It also reads the maze.txt file and sets up the board.
 *The destroyMaze function clears all memory allocated to the maze. The solveMazeDFS
 *uses depth-first search to determine where in the maze the program should move
 *to reach the exit.
 *partners: ipatel28
 * */


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    // create new file
   FILE *myfile;
	myfile = fopen(fileName,"r");
	int width, height;
	//scan width and height
	fscanf(myfile, "%d %d\n",&width,&height);

//	maze_t* temp = (maze_t*)malloc(sizeof(maze_t));
	//store maze in file into array
	char line[52][52];
	int i = 0;
	while(fgets(line[i], sizeof(line),myfile)!=NULL){
	//	fputs(line[i],stdout);
		i++;
	}
//	printf("%c", line[9][10]);






	//code to find where S is located

	int startColumn = 0;
	int startRow = 0;
	int endColumn = 0;
	int endRow=0;
	int x,j;
	int test = 0;

	for(x=0;x<52;x++)
	{
		for(j = 0;j<52;j++)
		{
			if((int) line[x][j] == 10 )
			{
				startRow++;
				break;
			}

			if(line[x][j] == 'S')
			{
				test = 1;
				startColumn = j;
				break;
			}

		}
		if(test == 1)
		{
			break;
		}
	}

	//Code to find where E is located
	test = 0;
	for(x=0;x<52;x++)
	{
		for(j = 0;j<52;j++)
		{
			if( (int)line[x][j] == 10 )
			{
				endRow++;
				break;
			}

			if(line[x][j] == 'E')
			{
				test = 1;
				endColumn = j;
				break;
			}

		}
		if(test == 1)
		{
			break;
		}
	}

	//Allocate Memory for cells and maze_t
	maze_t* temp = (maze_t*) malloc(sizeof(maze_t));
	temp->width = width;
	temp->height = height;
	temp->startColumn = startColumn;
	temp->startRow = startRow;
	temp->endColumn = endColumn;
	temp->endRow = endRow;
//printf("%d %d %d %d %d %d ", temp->width,temp->height, temp->startColumn,temp->startRow,temp->endColumn,temp->endRow);
	//Allocated rows
	temp->cells = (char**) malloc(sizeof(char*) * height);
	//allocated columns
	for(i=0;i<height;i++){
		temp->cells[i] = (char*) malloc(sizeof(char) * width);
	}
	//Store values in temp array into struct **cells
	//printf("%c ", line[9][10]);
	for(i=0;i < height; i++)
	{
		for(j = 0;j<width;j++)
		{
		/*	int k = i;
			if(i == height -1){
				k = height -1;
			}*/
			temp->cells[i][j] = line[i][j];
	}
	}
//	printf("%c", temp->cells[3][10]);
	//close file

	fclose(myfile);
	//return pointer
	return temp;
	//printf("%d %d %d %d", startRow, startColumn,endRow,endColumn);

//	maze_t* temp = (maze_t*)malloc(sizeof(maze_t));

	//temp->cells = (cells**) malloc(sizeof(cells*) * INSERT NUMBER OF ROWS);

	//Allocate memory for the maze_t structure and the cells
	//	for(int i=0)
//	free(temp);

 return NULL;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	int height = maze->height;
	int i;
	//free columns
	for(i=0;i<height;i++){
		free(maze->cells[i]);
	}
	//free rows
	free(maze->cells);
	//free struct
	free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j;
	for(i = 0;i<maze->height;i++)
	{
		for(j=0;j<maze->width;j++)
		{
			//print values
			printf("%c", maze->cells[i][j]);
		//	printf("%d", maze->width);
		//	once we reach end of array print new line
			if(j == maze->width -1)
			{
				printf("\n");
				}

		}

	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
//One time checker
int tempD = 0;
int solveMazeDFS(maze_t * maze, int col, int row)
{
	    // Your code here. Make sure to replace following line with your own code.
    char temp = maze->cells[row][col];
	//Check if out of bounds
if(row < 0 || row >= maze->height)
		return 0;
	//Check if out of bounds
	if(col < 0 || col >= maze->width)
		return 0;


	//check if we reach the end
//	printf("%c", temp);
	if(temp == END)
	{
		return 1;
		//Check if empty or start
	}else if(temp == EMPTY || temp == START){
		if(temp == START ){
		//one run this method once
		if(tempD == 0){
			tempD++;
		if(solveMazeDFS(maze,col,row+1))
			return 1;
		if(solveMazeDFS(maze,col,row-1))
			return 1;
		if(solveMazeDFS(maze,col+1,row))
			return 1;
		if(solveMazeDFS(maze,col-1,row))
			return 1;
		}
	}else{
		//If not at start do normal protocol
		maze->cells[row][col] = '*';
		if(solveMazeDFS(maze,col,row+1))
			return 1;
		if(solveMazeDFS(maze,col,row-1))
			return 1;
		if(solveMazeDFS(maze,col+1,row))
			return 1;
		if(solveMazeDFS(maze,col-1,row))
			return 1;

		maze->cells[row][col] = VISITED;
		}

	}


	return 0;
}
