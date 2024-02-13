# (C) Algoritmo e Estrutura de Dados 2023/2024
# 
# AUTORES: Francisco Apolinário
#          Neelam Visueshcumar
#
# Para compilar o programa: make
#----------------------------------------------------------------------

CC = gcc
CFLAGS = -Wall -std=c99 -O3

tileblaster: main.o general.o files.o connectivity.o structs.o problems.o stack.o list.o
	$(CC) $(CFLAGS) -o tileblaster main.o general.o files.o connectivity.o structs.o problems.o stack.o list.o

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

problems.o: problems.c problems.h
	$(CC) -c $(CFLAGS) problems.c

files.o: files.c files.h
	$(CC) -c $(CFLAGS) files.c

structs.o: structs.c structs.h
	$(CC) -c $(CFLAGS) structs.c

connectivity.o: connectivity.c connectivity.h
	$(CC) -c $(CFLAGS) connectivity.c

stack.o: stack.c stack.h
	$(CC) -c $(CFLAGS) stack.c

list.o: list.c list.h
	$(CC) -c $(CFLAGS) list.c

general.o: general.c general.h
	$(CC) -c $(CFLAGS) general.c

clean:
	rm -f *.o *.tileblasts tileblaster *~
