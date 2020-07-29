//
//  fileio.h
//  filedistance
//
//  Created by Lorenzo Tanganelli on 14/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#ifndef fileio_h
#define fileio_h

#include <stdio.h>
#include "stackoperation.h"

/*
Function to write a string into a file.
 */
void stringToFile(char *fOutput, char *string);

/*
Function to read a file and return a string
 */
char *fileToString(char *file);

/*
Function to write a stack of instructions to a .bin file
*/
void writeBinFile(StackCommand *stack, FILE *fbin);

/*
Function to read a stack of instructions from a .bin file
 */
StackCommand *readBinFile(char *fModify);

/*
Function to generate the .bin file
given a stack of instructions.
*/
void generateBinFile(StackCommand *stack, char *fOutput);

/*
Function to edit a file according to
the instructions saved in the bin file
*/
void modifyFile(char *fInput, char *fModify, char *fOutput);


#endif /* fileio_h */
