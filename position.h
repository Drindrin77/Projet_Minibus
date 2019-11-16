#ifndef POSITION_HEADER
#define POSITION_HEADER

#include <math.h>

typedef struct Position{
    int X;
    int Y;        
}Position;

double distancePositions(Position pos1, Position pos2);
int samePosition(Position pos1, Position pos2);

#endif