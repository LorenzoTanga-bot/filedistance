//
//  Queue.c
//  filedistance
//
//  Created by Lorenzo Tanganelli on 14/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#include "stackdirectory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Function to create a new node to add to the stack.
 */
StackDirectory *newNodeDirectory(){
    StackDirectory *queueNode = (StackDirectory*)malloc(sizeof(StackDirectory));
    queueNode->distance = (unsigned int)malloc(sizeof(unsigned int));
    queueNode->path = (char*) malloc((1)*sizeof(char));
    queueNode->next = NULL;
    return queueNode;
}

int isEmptyDirectory(StackDirectory *root){
    return !root;
}

void insertNode(StackDirectory **root, StackDirectory *newNode){
    StackDirectory *head = *root;
    if(isEmptyDirectory(*root)){
        *root = newNode;
        return;
    }
    if(head->distance > newNode->distance){
        newNode->next = *root;
        *root = newNode;
    }else{
        while(head->next != NULL && head->next->distance < newNode->distance)
            head = head->next;
        
        newNode->next = head->next;
        head->next = newNode;
    }
}

void pushDirectory(StackDirectory **root, char *path, unsigned int distance){
    StackDirectory *newNode = newNodeDirectory();
    newNode->distance = distance;
    newNode->path = realloc(newNode->path, strlen(path));
    newNode->path = path;
    insertNode(root, newNode);
    
}

void popDirectory(StackDirectory **root){
    StackDirectory *tmp = *root;
    if(!isEmptyDirectory(*root)){
        *root = (*root)->next;
        free(tmp);
    }
}
