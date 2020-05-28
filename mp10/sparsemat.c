#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* This program takes a sparse matrix from a text file and operates on it.
The load_tuples function takes the file, reads it, and creates a linked list
where each node represnts a non-zero cell in the matrix. The gv_tuples function
returns the value of a certain cell in the matrix given a matrix, row, and
column. The set_tuples function add, removes, or changes a node depending on
whether or not the node exists and/or has a non-zero value in it or not. The
function will delete a node if its value is to be set to zero. The save_tuples
function writes the final sparse matrix to a file in an ordered ascending
fashion. The add_tuples function takes in two matrices as inputs and adds their
values together and stores it in a new matrix which it returns. The mult_tuples
function does the same except performs multiplication instead of addtion. Both
the add and mult functions only perform operations of non-zero cells to save
time and memory resources. The destroy_tuples function frees all matrices and
nodes on the heap created in this program.

partner: ipatel28 */


//loads a file and creates a matrix based on the text in the file
sp_tuples * load_tuples(char* input_file)
{

    //loads file in read only manner and reads first two values
    FILE *tuplesIndex = fopen(input_file, "r");
    sp_tuples *sparseMatrix = (sp_tuples *) malloc(sizeof(sp_tuples));
    int numRow, numCol;
    fscanf(tuplesIndex, "%d %d\n", &numRow, &numCol);

    //sets width and height of the matrix as well as its non-zero value
    sparseMatrix->m = numRow;
    sparseMatrix->n = numCol;
    sparseMatrix->nz = 0;

    //declares variables for matrix
    int row, col;
    double value;
    sparseMatrix->tuples_head = NULL;

    //reads text files and creates nodes with the row, col, and value given by
    //the text file
    int tuple = fscanf(tuplesIndex, "%d %d %lf\n", &row, &col, &value);
    while(tuple != EOF && tuple != 0)
    {
      set_tuples(sparseMatrix, row, col, value);
      tuple = fscanf(tuplesIndex, "%d %d %lf\n", &row, &col, &value);

    }

    //closes file and returns matrix
    fclose(tuplesIndex);
    return sparseMatrix;
}


//returns value of a certain cell given matrix, row, and column
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
  //creates a new temporary node and sets to the head node of the matrix
  sp_tuples_node *temp;
  temp = mat_t->tuples_head;

  //checkes every node for the given row and column. If there is a match, it
  //returns the value. If row and column do not exsist, then 0 is returned
  while(temp != NULL)
  {
    if(temp->row == row && temp->col == col)
    {
      return temp->value;
    }
    else
    {
      temp = temp->next;
    }
  }
  return 0;
}


//adds, removes, or changes the nodes in a given linked list to a certain value
//and row and column provided by the program
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  //if the given value is equal to zero, delete the node
  if(value == 0)
  {

    //create a new node points to the head node
    sp_tuples_node *current = mat_t->tuples_head;
    sp_tuples_node *previous = NULL;

    //While traversing through the linked list, if there is a node with the
    //given row and column, remove it and set the previous node's pointer to
    //the pointer of the deleted node
    while(current != NULL)
    {
      if(previous == NULL && current->row == row && current->col == col)
      {
        mat_t->tuples_head = mat_t->tuples_head->next;
        free(current);
        mat_t->nz--;
        return;
      }
      else if(current->row == row && current->col == col)
      {
        previous->next = current->next;
        free(current);
        mat_t->nz--;
        return;
      }

      //change prevoius node to current node and current node to next node
      previous = current;
      current = current->next;

    }
    return;
  }

  //if the head node does not exsist, new node will become the head node and
  //will point to the tail (NULL)
  if(mat_t->tuples_head == NULL)
  {
    mat_t->tuples_head = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
    mat_t->tuples_head->row = row;
    mat_t->tuples_head->col = col;
    mat_t->tuples_head->value = value;
    mat_t->tuples_head->next = NULL;
    mat_t->nz++;
    return;
  }


  //if given values do not exsist in linked list, create a new node and find the
  //correct place in the linked list and put the node there
  sp_tuples_node *newNode = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
  newNode->row = row;
  newNode->col = col;
  newNode->value = value;

  //creates a current node and a next node
  sp_tuples_node *current1 = mat_t->tuples_head;
  sp_tuples_node *nextTuple = current1->next;

  //While traversing through the current node, check where the node should be
  //placed in the linked list and place it there
  while(current1 != NULL)
  {

    //intializes variables to represent a certain node's position in the list
    int currentVal = current1->row * mat_t->n + current1->col;
    int newVal = newNode->row * mat_t->n + newNode->col;
    int head = mat_t->tuples_head->row * mat_t->n + mat_t->tuples_head->col;

    //if new node is before head node, place it before the head node and change
    //new node's pointer to head node
    if(newVal < head)
    {
      newNode->next = mat_t->tuples_head;
      mat_t->tuples_head = newNode;
      mat_t->nz++;
      return;
    }

    //if new node is tail, change pointer to NULL and set previous node's
    //pointer to new node
    else if((nextTuple == NULL) && (newVal > currentVal))
    {
      newNode->next = NULL;
      current1->next = newNode;
      mat_t->nz++;
      return;
    }

    //if new node is equal to the position of current node, override the current
    //node's value to the value of the new node
    else if(currentVal == newVal)
    {
      current1->value = newNode->value;
      mat_t->nz++;
      return;
    }

    //if new node occurs after the current node, set the current node's pointer
    //to the new node and set the new node's pointer to the next node
    else if(newVal > currentVal && newVal < (nextTuple->row * mat_t->n + nextTuple->col))
    {
      newNode->next = nextTuple;
      current1->next = newNode;
      mat_t->nz++;
      return;
    }

    //set current node to next node in linked list and check if it is the tail
    current1 = nextTuple;
    if(nextTuple != NULL)
    {
      nextTuple = nextTuple->next;
    }
  }
}



//writes the sparse matrix to a file
void save_tuples(char * file_name, sp_tuples * mat_t)
{
  //opens file and initliazes it to "write" only
  FILE *saveFile;
  saveFile = fopen(file_name, "w");

  //prints the height and weight of the matrix to the file
  fprintf(saveFile, "%d %d\n", mat_t->m, mat_t->n);

  //prints to row, col, and value of every node in the linked list to the file
  while(mat_t->tuples_head != NULL)
  {
    fprintf(saveFile, "%d %d %lf\n", mat_t->tuples_head->row, mat_t->tuples_head->col, mat_t->tuples_head->value);
    mat_t->tuples_head = mat_t->tuples_head->next;
  }
	return;
}


//takes two matrices as inputs and performs addition and returns another  matrix
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
  //checks if the the given matrices are of the same width and height
  if(matA->m == matB->m && matA->n == matB->n)
  {
    //creates a new matrix with the height and width of the provided ones
    sp_tuples *matC = (sp_tuples *) malloc(sizeof(sp_tuples));
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

    //creates a new node that points to the head node
    sp_tuples_node *head = matA->tuples_head;

    //copy matrix A to the new matrix
    while(head != NULL)
    {
      if(head->value != 0)
      {
        set_tuples(matC, head->row, head->col, head->value);
      }
      head = head->next;
    }

    //sets node to the head node of matrix B
    head = matB->tuples_head;

    //adds the value of matrix B to matrix C and saves it in matrix C
    while(head != NULL)
    {
      if(head->value != 0)
      {
        double tempValue = gv_tuples(matC, head->row, head->col);

        if(tempValue != 0)
        {
          tempValue = tempValue + head->value;
          set_tuples(matC, head->row, head->col, tempValue);
        }
        else
        {
          set_tuples(matC, head->row, head->col, head->value);
        }
        head = head->next;
      }
    }
    return matC;
  }
  return NULL;
}


//given two matrices perform matrix multiplication
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{

  //checks if the matrix is valid
  if(matA->n == matB->m)
  {

    //creates new matrix with the correct height and width
    sp_tuples *matC2 = (sp_tuples *) malloc(sizeof(sp_tuples));
    matC2->m = matA->m;
    matC2->n = matB->n;
    matC2->nz = 0;


    //creates temporary head nodes that point to the head of the two other
    //matrices
    sp_tuples_node *headofA = matA->tuples_head;
    sp_tuples_node *headofB = matB->tuples_head;


    //go through each node and perform multiplication if the column valuee of B
    //equals the row value of matrix A
    while(headofA != NULL)
    {
      while(headofB != NULL)
      {
        if(headofB->row == headofA->col)
        {
          double tempVal = gv_tuples(matC2, headofA->row, headofB->col);
          double product = headofB->value * headofA->value;
          tempVal = tempVal + product;
          set_tuples(matC2, headofA->row, headofB->col, tempVal);
          headofB = headofB->next;
        }
        else
        {
          headofB = headofB->next;
        }
      }
      headofA = headofA->next;
      headofB = matB->tuples_head;
    }
    return matC2;
  }
  return NULL;
}


//frees up space by deleting nodes and linked lists
void destroy_tuples(sp_tuples * mat_t)
{
    free(mat_t);
    return;
}
