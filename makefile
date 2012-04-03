CFLAGS=`pkg-config --libs --cflags gtk+-2.0`

all: rjFunction.o renju.o renju

renju:	renju.o rjFunction.o
	gcc renju.o rjFunction.o -o renju $(CFLAGS)

renju.o: renju.c renju.h
	gcc -c renju.c $(CFLAGS)

rjFunction.o: rjFunction.c renju.h
	gcc -c rjFunction.c $(CFLAGS)

lei: lei.o
	gcc lei.o -o lei $(CFLAGS)

lei.o: ./src/lei.c
	gcc -c ./src/lei.c $(CFLAGS)

clean:
	rm -f renju *.o
