
output: one.o
	g++ one.o -o output

one.o: one.cpp two.h three.h
	g++ -c one.cpp

clean:
	rm *.o output