# (C) Algoritmo e Estrutura de Dados 2023/2024
# 
# AUTORES: Francisco Apolinário
#          Neelam Visueshcumar
#
# Para compilar o programa: make
#----------------------------------------------------------------------

CC = gcc
CFLAGS = -Wall -std=c99 -O3

tileblaster: main.o general.o files.o connectivity.o table.o verifications.o
	$(CC) $(CFLAGS) -o tileblaster main.o general.o files.o connectivity.o table.o verifications.o

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

files.o: files.c files.h
	$(CC) -c $(CFLAGS) files.c

table.o: table.c table.h
	$(CC) -c $(CFLAGS) table.c

verifications.o: verifications.c verifications.h
	$(CC) -c $(CFLAGS) verifications.c

connectivity.o: connectivity.c connectivity.h
	$(CC) -c $(CFLAGS) connectivity.c

general.o: general.c general.h
	$(CC) -c $(CFLAGS) general.c

clean:
	rm -f *.o *.singlestep tileblaster *~
