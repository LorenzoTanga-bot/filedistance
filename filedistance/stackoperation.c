//
//  stack.c
//  filedistance
//
//  Created by Lorenzo Tanganelli on 10/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#include "stackoperation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Function to create a new node to add to the stack.
 */
StackCommand *newNodeStack(){
    StackCommand *stackNode = (StackCommand*)malloc(sizeof(StackCommand));
    stackNode->type = (edit_type)malloc(sizeof(edit_type));
    stackNode->character = (char)malloc(sizeof(char));
    stackNode->position  = (unsigned int)malloc(sizeof(unsigned int));
    stackNode->next = NULL;
    return stackNode;
}

int isEmptyCommand(StackCommand *root)
{
    return !root;
}

void pushCommand(StackCommand **root, edit_type type, unsigned int position, char character){
    StackCommand *stackNode = newNodeStack();
    stackNode->type = type;
    stackNode->position = position;
    stackNode->character = character;
    stackNode->next = *root;
    *root = stackNode;
}

void popCommand(StackCommand **root){
    StackCommand *tmp = *root;
    if(!isEmptyCommand(*root)){
        *root = (*root)->next;
        free(tmp);
    }
}

char *getType(StackCommand *node){
    if(!isEmptyCommand(node)){
        switch (node->type) {
            case SET:
                return "SET";
            case ADD:
                return "ADD";
            case DEL:
                return "DEL";
        }
    }
    else return "";
    
}
