#ifndef gameStart
#define gameStart

#include "initB.hpp"
#include "movep.hpp"
#include <time.h>
#include <thread>
#include <chrono>
pair<int, int> parse(string);
void startGame(pair<pair<Player*, Player*>,Square**>);
void turn(Player*, Player *, Square**, string);
void player_turn(Player*, Player *, Square**, string*);
void cpu_turn(Player *, Player *, Square **, string *);

#endif
