
output: test.o
	gcc test.o -o output

test.o: test.c dirutil.h disputil.h termutil.h util.h inpututil.h keyread.h commandutil.h searchutil.h
	gcc -c test.c

clean:
	rm *.o output
