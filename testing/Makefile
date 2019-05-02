# -*- MakeFile -*-

#target: dependencies
#	action

geom: geom.o gd.o
	gcc geom.o gd.o -o geom -lm

geom.o: geom.c gd.h
	gcc -c geom.c

gd.o: gd.c
	gcc -c gd.c

clean:
	rm *.o geom
