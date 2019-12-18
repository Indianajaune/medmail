medmail: main.o medmail.o
	gcc main.o medmail.o -o medmail

main.o: main.c medmail.h
	gcc -c main.c -Wall -std=c11

medmail.o: medmail.c medmail.h
	gcc -c medmail.c -Wall -std=c11
