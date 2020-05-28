#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// This program is a sudoku solver. It takes an incomplete sudoku grid and fills in the correct numbers
// to complete the sudoku board. This is done by using several functions. The is_val_in_row determines
// if the number is in the row while the is_val_in_col determines whether the number is in the column or
// not. The is_val_in_3x3_zone checks if the number is in the 3x3 zone corresponding to a certain cell.
// The is_val_valid combines all these functions together to determine if a certain number is valid
// and whether or not that number can be placed in that location. The solve_sudoku function traverses
// through each cell and determines if that cell is unassigned (value = 0), and if it is, it determines
// which number should be put there to complete the sudoku board.
//
// partners: ipatel28




// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int j = 0; j < 9; j++) // traverses through each row
  {
    if(val == sudoku[i][j]) // checks whether or not the the value exists in that row
    {
      return 1; // returns true if the value exists
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int i = 0; i < 9; i++) // traverses through each column
  {
    if(val == sudoku[i][j]) // checks whether or not the value exists in that column
    {
      return 1; // returns true if the value exists
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int counter = 0;
  if(i >= 0 && i < 3 && j >= 0 && j < 3) // traverses through the top left corner zone
  {
    for(int row = 0; row < 3; row++)
    {
      for( int col = 0; col < 3; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  else if(i >= 3 && i < 6 && j >= 0 && j < 3) // traverses through the top middle zone
  {
    for(int row = 3; row < 6; row++)
    {
      for( int col = 0; col < 3; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  else if(i >= 6 && i < 9 && j >= 0 && j < 3) // traverses throught the top right corner zone
  {
    for(int row = 6; row < 9; row++)
    {
      for( int col = 0; col < 3; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  else if(i >= 0 && i < 3 && j >= 3 && j < 6) // traverses through the middle left zone
  {
    for(int row = 0; row < 3; row++)
    {
      for( int col = 3; col < 6; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  else if(i >= 3 && i < 6 && j >= 3 && j < 6) // traverses through the center zone
  {
    for(int row = 3; row < 6; row++)
    {
      for( int col = 3; col < 6; col++)
      {
        if(sudoku[row][col] == val) // if value exists in the zone, increase counter
        {
          counter += 1;
        }
      }
    }
  }
  else if(i >= 6 && i < 9 && j >= 3 && j < 6) // traverses through the middle right zone
  {
    for(int row = 6; row < 9; row++)
    {
      for( int col = 3; col < 6; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  else if(i >= 0 && i < 3 && j >= 6 && j < 9) // traverses through the bottom left corner zone
  {
    for(int row = 0; row < 3; row++)
    {
      for( int col = 6; col < 9; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  else if(i >= 3 && i < 6 && j >= 6 && j < 9) // traverses through the bottom middle zone
  {
    for(int row = 3; row < 6; row++)
    {
      for( int col = 6; col < 9; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  else if(i >= 6 && i < 9 && j >= 6 && j < 9) // traverses through the bottom right corner zone
  {
    for(int row = 6; row < 9; row++)
    {
      for( int col = 6; col < 9; col++)
      {
        if(sudoku[row][col] == val)
        {
          counter += 1; // if value exists in the zone, increase counter
        }
      }
    }
  }
  if(counter == 1) // if counter equals one, then the value occurs
  {
    return 1; // return true
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);


  // BEG TODO
  if(((is_val_in_row(val, i, sudoku)) == 0) && ((is_val_in_col(val, j, sudoku)) == 0) && ((is_val_in_3x3_zone(val, i, j, sudoku)) == 0)) // checks whether or not the number is in the row, column, and 3x3 zone
  {
    return 1; // returns true if the number does not exist in the row, column, or 3x3 zone
  }
  return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
int i, j;
int flag = 1; // initializes and declares variables
for(i = 0; i < 9; i++) // traverses through every row
{
  for(j = 0; j < 9; j++) // traverses through every column
  {
    if(sudoku[i][j] == 0)
    {
      flag = 0; // if there is a value in the cell that is blank, set flag to 0;
      break;
    }
  }
  if(flag == 0)
  {
    break; // if flag equals 0, break out of the loop
  }
}
if(flag == 1)
{
  return 1; // if flag equals 1, then sudoku board is completed
}
for(int num = 1; num <= 9; num++) // try every number between 1 and 9
{
  if(is_val_valid(num, i, j, sudoku) == 1) // check if number is valid
  {
    sudoku[i][j] = num; // assign number to cell
    if(solve_sudoku(sudoku) == 1) // check again if the sudoku board is completed
    {
      return 1; // return 1 if the sudoku board is completed
    }
    sudoku[i][j] = 0; // if sudoku board is not completed, try another number
  }
}


  return 0; // return 0 if board does not complete
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
