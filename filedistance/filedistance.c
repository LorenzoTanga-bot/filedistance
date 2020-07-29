//
//  filedistance.c
//  filedistance
//
//  Created by Lorenzo Tanganelli on 10/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#include "filedistance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.h"
#include "levensthein.h"
#include "fileio.h"

void distance(char *fFirst, char *fSecond){
    start_timer();
    int distance = levenstheinDistance(fSecond, fFirst);
    
    printf("\nEDIT DISTANCE: %i \n", distance);
    printf("TIME: %lf \n\n", stop_timer());
}

void distanceOutput(char *fFirst, char *fSecond, char *fOutput){
    start_timer();
    char *sFirst = fileToString(fSecond);
    char *sSecond = fileToString(fFirst);
    
    int **matrix = matrixGenerate(sFirst, sSecond);
    generateBinFile(matrixCalculate(matrix, sFirst, sSecond), fOutput);
    deallocateMatrix((int) strlen(sFirst)+1, matrix);
    free(sFirst);
    free(sSecond);
    
    printf("TIME: %lf\n", stop_timer());
}

void apply(char *fInput, char *fModify, char *fOutput){
    start_timer();
    modifyFile(fInput,fModify,fOutput);
    printf("TIME: %lf\n", stop_timer());
}

void recursiveSearch(char *fInput, char *directory, unsigned int limit){
    start_timer();
    recursiveLevensthein(fInput, directory, limit);
    printf("TIME: %lf\n", stop_timer());
}

void search(char *fInput, char *directory){
    recursiveSearch(fInput, directory, 0);
}

void searchAll(char *fInput, char *directory, int limit){
    recursiveSearch(fInput, directory, limit);
}
