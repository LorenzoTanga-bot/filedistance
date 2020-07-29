//
//  filedistance.h
//  filedistance
//
//  Created by Lorenzo Tanganelli on 10/07/2020.
//  Copyright © 2020 Lorenzo Tanganelli. All rights reserved.
//

#ifndef filedistance_h
#define filedistance_h

/*
Function that calculates the edit distance between "fFirst" and "fSecond".
 */
void distance(char *fFirst, char *fSecond);

/*
Function to generate the .bin file with instructions
for modifying the "fFirst" to have distance 0 from "fSecond".
*/
void distanceOutput(char *fFirst, char *fSecond, char *fOutput);

/*
Function that applies the changes stored in fModify to
fInput and saves the result in the fOutput file.
 */
void apply(char *fInput, char *fModify, char *fOutput);

/*
Function that returns the files contained in directory (and in
its subdirectory) which have minimum distance from fInput.
 */
void search(char *fInput, char *directory);

/*
Function that returns all files contained in directory (and in
its subdirectories) that have a limit of less than or equal to the fInput.
 */
void searchAll(char *fInput, char *directory, int limit);

#endif /* filedistance_h */
