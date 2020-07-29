CC = gcc
objects = main.o filedistance.o levensthein.o stackoperation.o stackdirectory.o fileio.o timer.o

all : filedistance

filedistance : $(objects)
	$(CC) -o filedistance $(objects)

main.o : main.c filedistance.h

filedistance.o : filedistance.c timer.h levensthein.h fileio.h stackoperation.h

levensthein.o : levensthein.c stackoperation.h stackdirectory.h fileio.h

fileio.o : fileio.c stackoperation.h

stackoperation.o : stackoperation.c

stackdirectory.o : stackdirectory.h

timer.o : timer.c

clean : 
	rm *.o filedistance