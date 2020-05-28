/* This program takes two inputs from the user and checks every value in between those
two numbers, including the numbers itself. The program checks whether each value is a
semiprime, meaning whether that number is a product of two prime numbers, or not by
determining whether the number and its prime factor are both prime numbers. The values
that are semiprime are printed onto the screen.

partners: ipatel28 */

#include <stdlib.h>
#include <stdio.h>

/* Declaration of functions */

int is_prime(int number);
int print_semiprimes(int a, int b);

/* The main function takes two inputs from the user and executes the functions */

int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   print_semiprimes(a,b);

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */

/* Takes an input and calculates whether that integer is a prime integer
or not by checking values from 2 to the given integer and calculating their
remainders */

int is_prime(int number)
{
  int c;

  if(number == 2)
    {
        c = 1;
        return c;
    }

    if(number == 1 || number == 0)
    {
        c = 0;
        return c;
    }

  for(int i = 2; i < number; i++)
    {
        if(number % i == 0)
        {
            c = 0;
            break;
        }
        else
        {
            c = 1;
        }
    }
        
    return c;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */

/* Checks whether the every value between the two input variables to determine
whether they are semiprime numbers or not. This is done by calling the is_prime
function. */

int print_semiprimes(int a, int b)
{
  int d = 0;
  for(int n = a; n <= b; n++)
  {
    for(int k = 2; k <= n-1; k++)
    {
      if(n % k == 0 && is_prime(k) == 1 && is_prime(n/k) == 1)
      {
          printf("%d ", n);
          d = 1;
          break;
      }     
    }
  }
  return d;
}
