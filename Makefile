
output: one.o
	gcc one.o -o output

one.o: one.c two.h three.h append.h
	gcc -c one.c

clean:
	rm *.o output