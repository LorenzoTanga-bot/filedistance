//
//  main.c
//  filedistance
//
//  Created by Lorenzo Tanganelli on 26/05/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filedistance.h"

void help(){
    printf("Edit distance: ./filedistance distance <fileA> <fileB> \n");
    printf("Generete output instraction: ./filedistance distance <fileA> <fileB> <fOutput> \n");
    printf("Apply instraction: ./filedistance apply <fInput> <fileM> <fOutput> \n");
    printf("Search file: ./filedistance search <fInput> <directory> \n");
    printf("Search file with limit: ./filedistance searchall <fInput> <directory> <limit> \n\n");
}

int main(int argc, char *argv[]) {
    
    if(argc == 1){
        help();
        exit(1);
    }else if (strcmp(argv[1], "distance") == 0){
        if (argc == 4) {
            distance(argv[2], argv[3]);
        }else if (argc == 5){
            distanceOutput(argv[2], argv[3], argv[4]);
        }else perror("Wrong number of arguments \n");
        
    }else if ((strcmp(argv[1], "apply") == 0) && (argc == 5)){
        apply(argv[2], argv[3], argv[4]);
        
    }else if ((strcmp(argv[1], "search") == 0)){
        if(argc == 4)
            search(argv[2], argv[3]);
        if(argc == 5){
            int limit = atoi(argv[4]);
            searchAll(argv[2], argv[3], limit);
        }
    }else perror("Wrong numeber of arguments \n");
    return 0;
}
