medmail: medmail.o main.o
	gcc medmail.o main.o -o medmail

medmail.o: medmail.c medmail.h
	gcc -c medmail.c -Wall -std=c11

main.o: main.c medmail.h
	gcc -c main.c -Wall -std=c11
