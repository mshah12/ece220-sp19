/* This program generates a random number using a seed. A seed is set which corresponds to a
mathematical computation resulting in a number. That number represents the soltuion to the problem.
The user then inputs 4 integers values which and tries to guess the four solutions. If the user guesses
the right integer and its correct location, the counter for 'perfect match' increases, and if the user
guesses the right integer in the wrong location, the counter for 'misplaced match' increases. If the user
does not guess any correct intgers, no counter is incremeted, and if the user enters an invalid input then
an error message is executed. The solutions and the inputs are compared by using a if-else statement and
comparing the integer with the solution in its place and the solutions in other places.

partners: ipatel28

*/

/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below

// This function takes an unsigned integer from the user and uses that integer value to generate a random seed value
// Any random function called will use the seed value to produce its random value

    int seed, ret_value, toreturn;
    char post[2];

    // Takes the users input as a string and converts to an integer

    ret_value = sscanf(seed_str, "%d%1s", &seed, post);
    if(ret_value == 1)
    {
      srand(seed);
      toreturn = 1;
    }
    else
    {
      printf("set seed: invalid_seed\n"); // Prints error message if seed value is invalid
      toreturn = 0;
    }
    return toreturn;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    // Generates random numbers from 1-8 based on the seed value
    // and assigns them to pointer values
    solution1 = (rand() % 8) + 1;
    solution2 = (rand() % 8) + 1;
    solution3 = (rand() % 8) + 1;
    solution4 = (rand() % 8) + 1;
    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4;
    guess_number = 1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two,
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

// Takes the user's input and check its values with the solution

char post[2];
int ret = sscanf(guess_str, "%d%d%d%d%1s", one, two, three, four, post);
if(ret != 4)
{
    printf("make_guess: invalid guess\n");
    return 0;
}

// Initializes variables to their respective values //

int guessarray[] = {*one, *two, *three, *four};
int solarray[] = {solution1, solution2, solution3, solution4};
int status[4] = {0, 0, 0, 0};
int pmatch = 0;
int mmatch = 0;

// Checks if user's guess is 4 integers between 1 and 8

int flag = 0;
for(int i = 0; i < 4; i++)
{
    for(int j = 1; j <= 8; j++)
    {
        if(guessarray[i] == j)
        {
            flag = flag + 1;
            break;
        }
    }
}

// Prints out error message if user's input is invalid //

if(flag != 4)
{
    printf("make_guess: invalid guess\n");
}

// Checks for perfect matches between the user's guesses and the solutions

for(int i = 0; i < 4; i++)
{
    if(guessarray[i] == solarray[i])
    {
        pmatch += 1;
        status[i] = 1;
    }
}

// Checks for misplaced matches between the user's guesses and the solutions

for(int j = 0; j < 4; j++)
{
    if(status[j] == 0)
    {
        for(int k = 0; k < 4; k++)
        {
            if(status[k] == 0 && guessarray[j] == solarray[k] && j != k)
            {
                mmatch += 1;
                break;
            }
        }
    }
}

// Prints out final message with the number of guesses and matches

printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, pmatch, mmatch);
guess_number++;
return 1;
}
