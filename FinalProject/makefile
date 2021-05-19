labapp: labapp.o zoomrecs.o
	gcc -o labapp labapp.o zoomrecs.o

labapp.o : labapp.c zoomrecs.h
	gcc -c labapp.c

zoomrecs.o: zoomrecs.c zoomrecs.h
	gcc -c zoomrecs.c

clean:
	rm labapp labapp.o zoomrecs.o
