// MagicSquares.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iomanip>
#include <iostream>
using namespace std;

/*
A 3x3 magic square is a 3x3 grid of the numbers 1-9 such that each row, column, and major diagonal adds up to 15. Here's an example:
8 1 6
3 5 7
4 9 2

The major diagonals in this example are 8 + 5 + 2 and 6 + 5 + 4.

Write a function that, given a grid containing the numbers 1-9, determines whether it's a magic square.
Use whatever format you want for the grid, such as a 2-dimensional array, or a 1-dimensional array of length 9, or a function that takes 9 arguments.
You do not need to parse the grid from the program's input, but you can if you want to.
You don't need to check that each of the 9 numbers appears in the grid: assume this to be true.

Example inputs/outputs:
[8, 1, 6, 3, 5, 7, 4, 9, 2] => true
[2, 7, 6, 9, 5, 1, 4, 3, 8] => true
[3, 5, 7, 8, 1, 6, 4, 9, 2] => false
[8, 1, 6, 7, 5, 3, 4, 9, 2] => false
*/

bool FIsMagicSquare( int dim, int* data )
{
   const int sum = ( ( dim * dim + 1 ) * dim ) / 2;

   // check each row
   for( int row = 0; row < dim; row++ )
   {
      int rowSum = 0;
      for( int col = 0; col < dim; col++ )
         rowSum += data[ row * dim + col ];

      if( rowSum != sum )
         return false;
   }

   // check each col
   for( int col = 0; col < dim; col++ )
   {
      int colSum = 0;
      for( int row = 0; row < dim; row++ )
         colSum += data[ row * dim + col ];

      if( colSum != sum )
         return false;
   }

   // for both diagonals
   int fDiagSum = 0;
   int rDiagSum = 0;
   for( int i = 0; i < dim; i++ )
   {
      fDiagSum += data[ i * dim + 1 ];
      rDiagSum += data[ ( dim - 1 ) * ( i + 1 ) ];
   }

   return fDiagSum == sum && rDiagSum == sum;
}

void PrintResult( int rows, int cols, int* data, const char* title, bool result )
{
   cout << title << "( [ ";
   for( int row = 0; row < rows; row++ )
   {
      int rowSum = 0;
      for( int col = 0; col < cols; col++ )
      {
         cout << setw( 2 ) << data[ row * cols + col ];
         if( row != rows || col != cols - 1 )
            cout << ", ";
      }
   }
   cout << " ] ) = " << ( result ? "true" : "false" ) << endl;
}

void RunDim3()
{
   const int dim = 3;
   int testCases[][ dim * dim ] = { { 8, 1, 6, 3, 5, 7, 4, 9, 2 },
                                    { 2, 7, 6, 9, 5, 1, 4, 3, 8 },
                                    { 3, 5, 7, 8, 1, 6, 4, 9, 2 },
                                    { 8, 1, 6, 7, 5, 3, 4, 9, 2 } };

   for( auto& testCase : testCases )
      PrintResult( dim, dim, testCase, "FIsMagicSquare", FIsMagicSquare( dim, testCase ) );
}

void RunDim4()
{
   const int dim = 4;
   int testCases[][ dim * dim ] = { { 7, 12, 1, 14, 2, 13, 8, 11, 16, 3, 10, 5, 9, 6, 15, 4 },
                                    { 12, 1, 14, 7, 13, 8, 11, 2, 3, 10, 5, 16, 6, 15, 4, 9 },
                                    { 14, 1, 12, 7, 13, 8, 11, 2, 3, 9, 5, 16, 6, 15, 4, 10 },
                                    { 12, 8, 9, 7, 13, 1, 11, 2, 3, 10, 5, 16, 15, 6, 4, 14 } };

   for( auto& testCase : testCases )
      PrintResult( dim, dim, testCase, "FIsMagicSquare", FIsMagicSquare( dim, testCase ) );
}

static bool FContains( int data[ 6 ], int val )
{
   for( int i = 0; i < 6; i++ )
   {
      if( data[ i ] == val )
         return true;
   }
   return false;
}

static bool FCanBeMagicSquare( int partialSquare[ 6 ] )
{
   // Find out which numbers are missing
   int missingNumbersFound = 0;
   int missingNumbers[ 3 ];
   for( int i = 1; i <= 9; i++ )
   {
      if( !FContains( partialSquare, i ) )
         missingNumbers[ missingNumbersFound++ ] = i;
   }

   if( missingNumbersFound != 3 )
      return false;

   // Create a full square to test with
   int fullSquare[ 9 ];
   for( int i = 0; i < 6; i++ )
      fullSquare[ i ] = partialSquare[ i ];

   int orders[ 6 ][ 3 ] = { { 0, 1, 2 },
                            { 0, 2, 1 },
                            { 1, 0, 2 },
                            { 1, 2, 0 },
                            { 2, 0, 1 },
                            { 2, 1, 0 } };
   for( int i = 0; i < 6; i++ )
   {
      fullSquare[ 6 ] = missingNumbers[ orders[ i ][ 0 ] ];
      fullSquare[ 7 ] = missingNumbers[ orders[ i ][ 1 ] ];
      fullSquare[ 8 ] = missingNumbers[ orders[ i ][ 2 ] ];

      if( FIsMagicSquare( 3 /*dim*/, fullSquare ) )
         return true;
   }

#if 0
   // Test all possible first values
   for( int i = 0; i < 3; i++ )
   {
      fullSquare[ 6 ] = missingNumbers[ i ];

      // Test all possible second values
      for( int j = 0; j < 3; j++ )
      {
         fullSquare[ 7 ] = missingNumbers[ j ];

         // Test all possible third values
         for( int k = 0; k < 3; k++ )
         {
            fullSquare[ 8 ] = missingNumbers[ k ];
            if( FIsMagicSquare( 3 /*dim*/, fullSquare ) )
               return true;
         }
      }
   }
#endif

   return false;
}

void RunCanBeMagicSquare3()
{
   const int dim = 3;
   int testCases[][ dim * ( dim - 1 ) ] = { { 8, 1, 6, 3, 5, 7 },
                                            { 2, 7, 6, 9, 5, 1 },
                                            { 3, 5, 7, 8, 1, 6 },
                                            { 8, 1, 6, 7, 5, 3 } };

   for( auto& testCase : testCases )
      PrintResult( dim, dim - 1, testCase, "FCanBeMagicSquare", FCanBeMagicSquare( testCase ) );
}

int main()
{
   RunDim3();
   RunDim4();
   RunCanBeMagicSquare3();
   cout << "Hit enter to continue";
   cin.get();

   return 0;
}

