# Makefile Projet Minibus C - S1
CC=gcc
CFLAGS=-Wall -Wextra -std=c99
OBJ=bus.o game.o player.o station.o passenger.o strategy.o command.o position.o
EXEC=IA_LEANNA

${EXEC}: $(OBJ)
	$(CC) -o ${EXEC} $(OBJ) -lm

game.o: game.c game.h player.h bus.h station.h passenger.h strategy.h
	$(CC) -c game.c -o game.o $(CFLAGS)

station.o: station.c station.h game.h
	$(CC) -c station.c -o station.o $(CFLAGS)

passenger.o: passenger.c passenger.h game.h
	$(CC) -c passenger.c -o passenger.o $(CFLAGS)

bus.o: bus.c bus.h game.h
	$(CC) -c bus.c -o bus.o $(CFLAGS)

player.o: player.c player.h game.h
	$(CC) -c player.c -o player.o $(CFLAGS)

command.o: command.c command.h game.h
	$(CC) -c command.c -o command.o $(CFLAGS)

strategy.o: strategy.c strategy.h command.h game.h
	$(CC) -c strategy.c -o strategy.o $(CFLAGS)

position.o: position.c position.h
	$(CC) -c position.c -o position.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(EXEC)
	rm -f *~