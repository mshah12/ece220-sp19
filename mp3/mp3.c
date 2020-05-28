#include <stdio.h>
#include <stdlib.h>

/* This program prints out a certain row index of
Pascal's triangle. This is done by taking an input
from the user to determine which row to print, and
then calculating the coefficents for that row by
using a for loop and the binomial coefficent
equation

partners: ipatel28 */

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here

  /* Declaration of variables. int row represents
     the row index and unsigned long coefficent represents
     the coefficents to be printed */

  unsigned long coefficent;

  /* Prints the coefficents for the a certain row. If row
  is zero, then the coefficent '1' is printed to represent
  Pascal's triangle */  

  for (int i = 0; i <= row; i++)
  {
    if (i == 0 || row == 0 || i == row)
    {
      coefficent = 1;
      printf("%lu ", coefficent);
    }
    else
    {
      coefficent = ((coefficent * (row + 1 - i)));
      coefficent = coefficent/i;
      printf("%lu ", coefficent);
    }
  }
  return 0;
}
