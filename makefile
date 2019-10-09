# Makefile Projet Minibus C - S1
CC=gcc
CFLAGS=-Wall -Wextra -std=c99
OBJ=bus.o jeu.o joueur.o station.o voyageur.o 

exec_jeu: $(OBJ)
	$(CC) -o exec_jeu $(OBJ)

jeu.o: jeu.c jeu.h joueur.h bus.h station.h voyageur.h
	$(CC) -c jeu.c -o jeu.o $(CFLAGS)

station.o: station.c station.h jeu.h
	$(CC) -c station.c -o station.o $(CFLAGS)

voyageur.o: voyageur.c voyageur.h jeu.h
	$(CC) -c voyageur.c -o voyageur.o $(CFLAGS)

bus.o: bus.c bus.h jeu.h
	$(CC) -c bus.c -o bus.o $(CFLAGS)

joueur.o: joueur.c joueur.h jeu.h
	$(CC) -c joueur.c -o joueur.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f exec_jeu
	rm -f *~