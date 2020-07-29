//
//  stackoperation.h
//  filedistance
//
//  Created by Lorenzo Tanganelli on 17/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#ifndef stackoperation_h
#define stackoperation_h

typedef enum {
    SET,
    ADD,
    DEL,
} edit_type;

typedef struct StackCommand{
    edit_type type;
    unsigned int position;
    char character;
    struct StackCommand* next;
}StackCommand;


/*
Function to add an operation to stack.
*/
void pushCommand(StackCommand **root, edit_type type, unsigned int position, char character);

/*
Function to remove an item from stack.
*/
void popCommand(StackCommand **root);

/*
Function to check if the stack is empty
*/
int isEmptyCommand(StackCommand *root);

/*
Function to get the associated string
to the edit_type present in the node.
*/
char *getType(StackCommand *node);

#endif /* stackoperation_h */
