//
//  fileio.c
//  filedistance
//
//  Created by Lorenzo Tanganelli on 14/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Function to execute a SET in the string: "string" in
 the position: "pos" of the character: "character".
 */
char *set(char *string, unsigned int pos, char character){
    string[pos] = character;
    return string;
}

/*
Function to execute a DEL in the string: "string" in the position: "pos"
 */
char *del(char *string, unsigned int pos){
    char *temp = NULL;
    temp = memmove(&string[pos], &string[pos + 1], strlen(string) - pos);
    return string;
}

/*
Function to execute an ADD in the string: "string"
in the position: "pos" of the character: "character"
 */
char *add(char *string, unsigned int pos, char character){
    int i, len;
    char *tmp = NULL;
    len = string ? (unsigned int)strlen(string) : 0;
    tmp = (char *)calloc(1, len + 2);
    if (tmp != NULL) {
        if (pos > len)
            pos = len;
        for (i = 0; i <pos; i++)
            tmp[i] = string[i];
        
        tmp[i] = character;
        for (; i < len; i++)
            tmp[i + 1] = string[i];
        
        tmp[i + 1] = '\0';
        free(string);
    }
    return tmp;
}

void stringToFile(char *fOutput, char *string){
    FILE *fout = fopen(fOutput, "w");
    if (fout == NULL) {
        perror("Could not open file");
        exit(1);
    }
    fputs(string, fout);
    fclose(fout);
}

char *fileToString(char *file){
    FILE *fin = fopen(file , "r");
    if(fin == NULL){
        perror("Could not open file");
        exit(1);
    }
    
    fseek(fin, 0L, SEEK_END);
    
    long sizeFin = ftell(fin);
    
    rewind(fin);
    
    char *str = calloc(1, sizeFin);
    
    if(str != NULL){
        fread(str , sizeFin, 1 , fin);
    }
    fclose(fin);
    return str;
}

void writeBinFile(StackCommand *stack, FILE *fbin){
    char* command = NULL;
    while (!isEmptyCommand(stack)) {
        command = getType(stack);
        for (int i = 0; i<3; i++) {
            fwrite(&command[i], sizeof(char), 1, fbin);
        }
        
        fwrite(&stack->position, sizeof(unsigned int), 1, fbin);
        if(strcmp("DEL",command)!=0)
           fwrite(&stack->character, sizeof(char), 1, fbin);
            
        popCommand(&stack);
    }
}

/*
 Function to add operations to the stack.
 */
void pushOperationInStack(StackCommand **root, char command, unsigned int position, char character){
    switch (command) {
        case 'S':
            pushCommand(root, SET, position, character);
            break;
        case 'A':
            pushCommand(root, ADD, position, character);
            break;
        case 'D':
            pushCommand(root, DEL, position, character);
            break;
    }
}


/*
Function to scroll through a .bin file
and add store operations to the stack.
 */
void scrollBin(FILE *fBin, StackCommand **root){
    
    char command;
    unsigned int position = 0;
    char character = '\0';
    
    while (!feof(fBin)) {
        
        fread(&command, sizeof(char), 1, fBin);
        fseek(fBin, 2, SEEK_CUR);
        fread(&position, (sizeof(unsigned int)), 1, fBin);
        if(command != 'D')
            fread(&character, (sizeof(char)), 1, fBin);
        pushOperationInStack(root, command, position, character);
        character = '\0';
    }
}

StackCommand *readBinFile(char *fModify){
    FILE *fBin = fopen(fModify, "rb+");
    if(fBin == NULL){
        perror("Could not open file");
        exit(1);
    }
    
    StackCommand *root = NULL;
    scrollBin(fBin, &root);
    
    fclose(fBin);
    return root;
}

void generateBinFile(StackCommand *stack, char *fOutput){
    FILE *fbin;
    if ((fbin = fopen(fOutput,"wb+")) == NULL){
        perror("Could not open file");
        exit(1);
    }
    writeBinFile(stack, fbin);
    fclose(fbin);
}

void modifyFile(char *fInput, char *fModify, char *fOutput){
    StackCommand *root = readBinFile(fModify);
    
    char *sInput = fileToString(fInput);
    
    while (!isEmptyCommand(root)) {
        switch (root->type) {
            case SET:
                sInput = set(sInput, root->position-1, root->character);
                break;
            case DEL:
                sInput = del(sInput, root->position-1);
                break;
            case ADD:
                sInput = add(sInput, root->position, root->character);
                break;
        }
        popCommand(&root);
    }
    
    stringToFile(fOutput, sInput);
    
}
