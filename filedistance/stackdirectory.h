//
//  stackdirectory.h
//  filedistance
//
//  Created by Lorenzo Tanganelli on 17/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#ifndef stackdirectory_h
#define stackdirectory_h

#include <stdio.h>

typedef struct StackDirectory{
    char *path;
    int distance;
    struct StackDirectory *next;
}StackDirectory;

StackDirectory *newQueueList(void);

/*
Function to check if the stack is empty
*/
int isEmptyDirectory(StackDirectory *root);

/*
Function to add an item to the priority stack: "root".
(priority is determined by distance)
*/
void pushDirectory(StackDirectory **root, char *path, unsigned int distance);

/*
Function to remove a lower priority item
(from the start) from the stack: "root".
*/
void popDirectory(StackDirectory **root);

#endif /* stackdirectory_h */
