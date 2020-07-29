# filedistance
The edit distance is a function that allows you to verify how far two sequences of bytes or strings are from each other. The Wagner-Fischer algorithm was used to calculate the edit distance. This function is calculated based on the minimum number of operations necessary to transform one string into the other. The operations are:

  • Add a character/byte;

  • Delete a character/byte;

  • Edit a character/byte.

# Program options
## Calculation of the distance between two files:

	./filedistance distance <fileA> <fileB>
	
the two files to be compared are passed as arguments and an output of the following form is generated:

	EDIT DISTANCE: distance
	TIME: computing time

## Generete output instraction:

	./filedistance distance <fileA> <fileB> <fOutput>

the two files to compareare are passed as arguments and in the file fOutput will be saved sequence of instructions necessary to transform the first file into the second.
The ADDnb, DELn, and SETnb values ('n' is an integer without a sign represented by 4 bytes identifying a position, while 'b' is a single byte representing a character) are stored in binary file.

## Applying of the modifies:

	./filedistance apply <fInput> <fileM> <fOutput> 
	
Apply the changes contained in the fileM file to fInput and save the result to the fOutput file.

## File search:
	
	./filedistance searchall <fInput> <directory> <limit>

limit is optional. if limit is present, all files contained in directories (and its subdirectories) that have a distance from fInput less than or equal to limit are returned to output. Otherwise it returns files contained in dir (and its subdirectories) that have minimum distance to fInput
