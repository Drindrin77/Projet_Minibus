#include "position.h"

double distancePositions(Position pos1, Position pos2){
    return sqrt(pow(pos2.X-pos1.X,2) + pow(pos2.Y - pos1.Y,2));
}

int samePosition(Position pos1, Position pos2){
    if(pos1.X==pos2.X && pos1.Y == pos2.Y)
        return 1;
    return 0;
}