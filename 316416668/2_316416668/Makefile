all:edf bd

edf: edf.o
	g++ -o edf edf.o

bd: bd.o
	g++ -o bd bd.o

edf.o : edf.cpp
	g++ -c edf.cpp

bd.o : bd.cpp
	g++ -c bd.cpp

clean:
	rm -f *.o bd edf