/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

/* This program takes a grid of alive and dead cells and determines how many aliveStable
neightbors are around a certain cell and whether or not that cell will live or die in the
next stage. This is done by calculating if the cells around a certain cell are alive or not
and depending on how many are alive and if the selected cell is alive, the cell will either
live on or die or come back alive. The countLiveNeighbor function operates by checking where
the cell is in the and checking the surrounding cells and updatiing a liveNeighbor counter. The
updateBoard function operates by checking whether a cell should be alive or dead, storing it into
another array, and copying that array to the board array. The aliveStable function works in similiar
fashion as checks the cell's current state and determines its next state. If any of the states differ,
the grid is not at equilibrium and will continue to for another iteration.

partners: ipatel28
*/


int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
{
   int liveNeighbor = 0, location;
   location = ((row * boardColSize) + col);
   if(row > 0 && row < (boardRowSize - 1) && col > 0 && col < (boardColSize - 1)) // checks middle of the grid. Not the edges or corners
   {
       if((board[location - 1]) ==  1)
       {
           liveNeighbor += 1;
       }
       if((board[location + 1]) ==  1)
       {
           liveNeighbor += 1;
       }
       if((board[location - boardColSize]) ==  1)
       {
           liveNeighbor += 1;
       }
       if((board[location - boardColSize - 1]) ==  1)
       {
           liveNeighbor += 1;
       }
       if((board[location - boardColSize + 1]) ==  1)
       {
           liveNeighbor += 1;
       }
       if((board[location + boardColSize]) ==  1)
       {
           liveNeighbor += 1;
       }
       if((board[location + boardColSize - 1]) ==  1)
       {
           liveNeighbor += 1;
       }
       if((board[location + boardColSize + 1]) ==  1)
       {
           liveNeighbor += 1;
       }
     }
     else if(col == 0 && row > 0 && row < (boardRowSize - 1)) // checks the left most edge
     {
       if((board[location + 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize + 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize + 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
     else if(col == (boardColSize - 1) && row > 0 && row < (boardRowSize - 1)) // checks the right most edge
     {
       if((board[location - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize - 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
     else if(row == 0 && col > 0 && col < (boardColSize - 1)) // checks the top most edge
     {
       if((board[location - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize + 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
     else if(row == (boardRowSize - 1) && col > 0 && col < (boardColSize - 1)) // checks the bottom most edge
     {
       if((board[location - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize + 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
     else if(col == 0 && row == 0) // checks the top left corner
     {
       if((board[location + 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize + 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
     else if(col == 0 && row == (boardRowSize - 1)) // checks the bottom left corner
     {
       if((board[location + 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize + 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
     else if(col == (boardColSize - 1) && row == 0) // checks the top right corner
     {
       if((board[location - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location + boardColSize - 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
     else if(col == (boardColSize - 1) && row == (boardRowSize - 1)) // checks the bottom right corner
     {
       if((board[location - 1]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize]) == 1)
       {
         liveNeighbor += 1;
       }
       if((board[location - boardColSize - 1]) == 1)
       {
         liveNeighbor += 1;
       }
     }
   return liveNeighbor; // returns the number of live cells surrounding a certain cell. Max return value can be 8
}
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize)
{
    int location; // initalizes and declares variables and array
    int size = ((boardRowSize * boardColSize) - 1);
    int compare[size];
    for(int i = 0; i < boardRowSize; i++) // checks every single cell in the array
    {
      for(int j = 0; j < boardColSize; j++)
      {
        location = ((i * boardColSize) + j);
        if(board[location] == 1) // if the cell is alive, determine whether the cell will stay alive or die
        {
          if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 2 || countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 3)
          {
            compare[location] = 1;
          }
          else
          {
            compare[location] = 0;
          }
        }
        else // if the cell is dead, determine whether the cell will stay dead or come alive
        {
          if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 3)
          {
            compare[location] = 1;
          }
          else
          {
            compare[location] = 0;
          }
        }
      }
    }
    for(int i = 0; i < boardRowSize; i++) // copys the new array into board array
    {
      for(int j = 0; j < boardColSize; j++)
      {
        location = ((i * boardColSize) + j);
        board[location] = compare[location];
      }
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize)
{
  int flag, location; // initializes variables
  for(int i = 0; i < boardRowSize; i++) // checks every single cell in the grid
  {
    for(int j = 0; j < boardColSize; j++)
    {
      location = ((i * boardColSize) + j);
      if(board[location] == 1) // if cell is alive, determine whether it will stay alive or die
      {
        if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j) < 2 || countLiveNeighbor(board, boardRowSize, boardColSize, i, j) > 3)
        {
            flag = 1; // set flag to 1 indicating the board will change
        }
      }
      else if(board[location] == 0) // if cell is dead, determine whether it will stay dead or alive
      {
        if(countLiveNeighbor(board, boardRowSize, boardColSize, i, j) == 3)
        {
          flag = 1; // set flag to 1 indicating the board will change
        }
      }
    }
  }
  if(flag == 1) // if flag is 1, then the board changes and is not at equilibrium
  {
    return 0;
  }
  return 1;
}
