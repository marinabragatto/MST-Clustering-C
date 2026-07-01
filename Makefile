objects := vector.o main.o search.o simbolTable.o string.o system.o page.o ioReader.o stringMapVector.o utils.o

all: $(objects)
	gcc -o trab2 $^ -lm

sources := vector.c main.c search.c simbolTable.c string.c system.c page.c ioReader.c stringMapVector.c utils.c
debug: $(sources)
	gcc -o teste $^ -g -lm


vector.o: vector.c
	gcc -c vector.c

main.o: main.c
	gcc -c main.c

search.o: search.c
	gcc -c search.c

simbolTable.o: simbolTable.c
	gcc -c simbolTable.c

string.o: string.c
	gcc -c string.c

system.o: system.c	
	gcc -c system.c

page.o: page.c	
	gcc -c page.c

ioReader.o: ioReader.c	
	gcc -c ioReader.c

stringMapVector.o: stringMapVector.c	
	gcc -c stringMapVector.c

utils.o: utils.c	
	gcc -c utils.c

page_rank.o:
	gcc -c page_rank.c

clean:
	rm -f *.o trab2 teste