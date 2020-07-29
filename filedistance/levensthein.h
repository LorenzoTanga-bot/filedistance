//
//  levensthein.h
//  filedistance
//
//  Created by Lorenzo Tanganelli on 10/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#ifndef levensthein_h
#define levensthein_h

#include "stackoperation.h"

/*
Function that calculates the edit distance
between file: "fFirst" and file: "fSecond", returns
the distance between the two files.
 */
int levenstheinDistance(char *fFirst, char *fSecond);

/*
Function that takes as input a matrix: "matrix"
and two strings: "sFirst" and "sSecond",
calculates the instructions for modifying
the first string in the second, adds them
to a stack and returns it.
 */
StackCommand *matrixCalculate(int **matrix, char *sFirst, char *sSecond);

/*
Function to generate and initialize the matrix
for Levensthein's algorithm,returns the calculated matrix.
 */
int **matrixGenerate(char *sFirst, char *sSecond);

/*
Function to deallocate the memory of the matrix
*/
void deallocateMatrix(int size, int** mat);

/*
Function to perform a recursive scan of the directory "path",
populate the stack and print it in terminal.
*/
void recursiveLevensthein(char *fInput, char *path, unsigned int distanceLimit);

#endif /* levensthein_h */
