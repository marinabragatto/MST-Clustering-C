objects := vector.o main.o search.o simbolTable.o string.o system.o page.o ioreader.o string_map_vector.o utils.o

all: $(objects)
	gcc -o trab2 $^

sources := vector.c main.c search.c simbolTable.c string.c system.c page.c ioreader.c string_map_vector.c utils.c
debug: $(sources)
	gcc -o teste $^ -g


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

ioreader.o: ioreader.c	
	gcc -c ioreader.c

string_map_vector.o: string_map_vector.c	
	gcc -c string_map_vector.c

utils.o: utils.c	
	gcc -c utils.c

clean:
	rm -f *.o trab2 teste