PROGRAMS = main.exe

.PHONY : clean

main.exe : PE_main_15231.o PE_functions_15231.o functions.h
	gcc -fopenmp PE_main_15231.o PE_functions_15231.o -o main.exe -lm

PE_functions_15231.o : PE_functions_15231.c
	gcc -c -fopenmp PE_functions_15231.c

PE_main_15231.o : PE_main_15231.c functions.h
	gcc -c -fopenmp PE_main_15231.c

clean :
	rm -f *.o $(PROGRAMS)
