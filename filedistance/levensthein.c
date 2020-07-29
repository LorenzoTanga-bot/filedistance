//
//  levensthein.c
//  filedistance
//
//  Created by Lorenzo Tanganelli on 10/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#include "levensthein.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "stackdirectory.h"
#include "fileio.h"

/*
Function to calculate the minimum between three numbers.
 */
int minimum(int a, int b, int c) {

    int min = a;

    if (b < min) min = b;
    if (c < min) min = c;

    return min;
}
/*
Function to calculate the operation to be performed on the basis of the "matrix".
 */
void calculateOperation(int *prev, int *add, int *del, int *set, int *curr, int *x, int *y, int **matrix){
    if (*x == 0) {
        *del = matrix[*x][*y-1];
        *prev = matrix[*x][*y-1];
    }else if(*y == 0){
        *add = matrix[*x-1][*y];
        *prev = matrix[*x-1][*y];
    }else if(*x > 0 && *y >0){
        *add = matrix[*x-1][*y];
        *set = matrix[*x-1][*y-1];
        *del = matrix[*x][*y-1];
        *prev = minimum(*del, *set, *add);
    }
    *curr = *prev;
}
/*
Function to add the operation inside the stack "stack".
*/
void pushOperation(int *prev, int *add, int *del, int *set, int *curr, int *x, int *y,char *sFirst, char *sSecond, StackCommand **stack){
    if(*prev == *set){
        if(sFirst[*x-1] != sSecond[*y-1]){
            pushCommand(stack, SET, *y, sFirst[*x-1]);
        }
        (*x)--;
        (*y)--;
    }else if(*prev == *add){
        pushCommand(stack, ADD, *y, sFirst[*x-1]);
        (*x)--;
        }
        else if(*prev == *del){
            pushCommand(stack, DEL, *y, ' ');
            (*y)--;
        }
}

StackCommand *matrixCalculate(int **matrix, char *sFirst, char *sSecond){
    int x = (int) strlen(sFirst);
    int y = (int) strlen(sSecond);
    StackCommand *stack = NULL;
    
    int curr = matrix[x][y];
    
    int prev = 0, add = 0, del = 0, set = 0;
    
    while (curr != 0) {
        calculateOperation(&prev, &add, &del, &set, &curr, &x, &y, matrix);
        pushOperation(&prev, &add, &del, &set, &curr, &x, &y, sFirst, sSecond, &stack);
        
    }
    return stack;
}

/*
Function to initialize the matrix: "matrix"
and calculate the Levensthein algorithm.
 */
int **initMatrix(int **matrix, char *sFirst, int x, char *sSecond, int y){
    int cost = 0;
    
    for(int i=1; i<x; i++){
        for(int j=1; j<y; j++){
            
            if (sFirst[i - 1] == sSecond[j - 1])
                cost = 0;
            else
                cost = 1;
            matrix[i][j] = minimum(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + cost);
        }
    }
    return matrix;
}

int **matrixGenerate(char *sFirst, char *sSecond){
    int x = (int) strlen(sFirst)+1;
    int y = (int) strlen(sSecond)+1;
    int **mat = malloc(sizeof(int*) * x);
    
    if(mat != NULL)
        for (int i=0; i<x; i++){
            mat[i] = calloc(1, sizeof(int) * y);
        }
    
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            mat[i][0]=i;
            mat[0][j]=j;
        }
    }
    return initMatrix(mat, sFirst, x, sSecond, y);
}

int levenstheinDistance(char *fFirst, char *fSecond){
    char *sFirst = fileToString(fSecond);
    char *sSecond = fileToString(fFirst);
    
    int x = (int) strlen(sFirst)+1;
    int y = (int) strlen(sSecond)+1;
    
    if (x == 0)
        return y;
    if (y == 0)
        return x;

    int **matrix = matrixGenerate(sFirst, sSecond);
    int distance = matrix[x-1][y-1];
    deallocateMatrix(x, matrix);
    free(sFirst);
    free(sSecond);
    return distance;
}

void deallocateMatrix(int size, int** mat){
    for (int i = 0; i<size; i++) {
        free(mat[i]);
    }
    free(mat);
}
/*
Function that pays a deep visit to the directory: "pBase"
and populates the "root" queue with the edit distance
between the files in the directory and the "fInput" file.
 */
void depthSearch(char *fInput, char *pBase, StackDirectory **root){
    struct dirent *dp;
    DIR *directory = opendir(pBase);
    
    if(!directory)
        return;
    while((dp = readdir(directory)) != NULL){
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".DS_Store")){
            char *path = (char*) malloc((strlen(pBase)+strlen(dp->d_name)+1)*sizeof(char));
            strcpy(path, pBase);
            strcat(path, "/");
            strcat(path, dp->d_name);
            if(dp->d_type != DT_DIR)
                pushDirectory(root, path, levenstheinDistance(fInput, path));
            else
                depthSearch(fInput, path, root);
        }
    }
    closedir(directory);
}

/*
function to print the queue of edit distances based
on the unsigned int limit: "distanceLimit"
 */

void printQueuePath(StackDirectory **root, unsigned int distanceLimit){
    if(isEmptyDirectory(*root))
        return;
    StackDirectory *node = *root;
    if(distanceLimit==0)
        distanceLimit = (*root)->distance;
    while (!isEmptyDirectory(*root) && (node = *root)->distance <= distanceLimit) {
        char *path = realpath(node->path, NULL);
        printf("%i\t\t%s\n", node->distance, path);
        popDirectory(root);
    }
}

void recursiveLevensthein(char *fInput, char *path, unsigned int distanceLimit){
    StackDirectory *root = NULL;
    depthSearch(fInput, path, &root);
    printQueuePath(&root, distanceLimit);
    
}
