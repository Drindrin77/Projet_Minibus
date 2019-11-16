# Makefile Projet Minibus C - S1
CC=gcc
CFLAGS=-Wall -Wextra -std=c99
OBJ=bus.o jeu.o joueur.o station.o voyageur.o strategie.o action.o position.o

exec_jeu: $(OBJ)
	$(CC) -o exec_jeu $(OBJ) -lm

jeu.o: jeu.c jeu.h joueur.h bus.h station.h voyageur.h strategie.h
	$(CC) -c jeu.c -o jeu.o $(CFLAGS)

station.o: station.c station.h jeu.h
	$(CC) -c station.c -o station.o $(CFLAGS)

voyageur.o: voyageur.c voyageur.h jeu.h
	$(CC) -c voyageur.c -o voyageur.o $(CFLAGS)

bus.o: bus.c bus.h jeu.h
	$(CC) -c bus.c -o bus.o $(CFLAGS)

joueur.o: joueur.c joueur.h jeu.h
	$(CC) -c joueur.c -o joueur.o $(CFLAGS)

action.o: action.c action.h jeu.h
	$(CC) -c action.c -o action.o $(CFLAGS)

strategie.o: strategie.c strategie.h action.h jeu.h
	$(CC) -c strategie.c -o strategie.o $(CFLAGS)

position.o: position.c position.h
	$(CC) -c position.c -o position.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f exec_jeu
	rm -f *~