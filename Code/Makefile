PROGRAMS = main.exe

.PHONY : clean

main.exe : PE_main_15231.o PE_functions_15231.o functions.h
	gcc PE_main_15231.o PE_functions_15231.o -o main.exe

PE_functions_15231.o : PE_functions_15231.c
	gcc -c PE_functions_15231.c

PE_main_15231.o : PE_main_15231.c functions.h
	gcc -c PE_main_15231.c

clean :
	rm -f *.o $(PROGRAMS)
