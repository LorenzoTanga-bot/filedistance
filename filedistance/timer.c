//
//  timer.c
//  filedistance
//
//  Created by Lorenzo Tanganelli on 12/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t start, end;

void start_timer(){
    start = clock();
};

double stop_timer(){
        end = clock();
        double execution_time = (double)(end - start) / CLOCKS_PER_SEC;
        return execution_time;
};
