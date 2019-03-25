#ifndef movep
#define movep

#include "initB.hpp"


NodeM *getMovesHelper(Player *,int, int, int, int, int, Square **, NodeM *);
NodeM *getMoves(Player *, char, unsigned int, unsigned int, Square **, NodeM *);
Square **moveToSquare(Player *, Player *, int, int, int, int, Square **);
NodeM *getTotalMoves(Player *, Square**);
NodeM *getRandNode(int, NodeM*);
bool searchForCheck(NodeM*);
#endif
