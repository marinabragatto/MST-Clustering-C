objects := indexador.o list.o main.o search.o simbolTable.o string.o system.o hash.o

all: $(objects)
	gcc -o trab2 $^

sources := indexador.c list.c main.c search.c simbolTable.c string.c system.c
debug: $(sources)
	gcc -o teste $^ -g

indexador.o : indexador.c
	gcc -c indexador.c

list.o: list.c
	gcc -c list.c

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

hash.o: hash.c
	gcc -c hash.c
	
linkedList.o: linkedList.c
	gcc -c linkedList.c
	
clean:
	rm -f *.o trab2 teste