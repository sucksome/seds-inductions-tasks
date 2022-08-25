# -*- Makefile -*-

exec: increase_by_x.o sum_of_N.o
	gcc -o exec increase_by_x.o sum_of_N.o

increase_by_x.o: increase_by_x.c inc.h
	gcc -c increase_by_x.c -o increase_by_x.o

sum_of_N.o: sum_of_N.c inc.h
	gcc -c sum_of_N.c -o sum_of_N.o

clean:
	rm *.o
	rm exec