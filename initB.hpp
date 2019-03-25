#ifndef initB
#define initB
#include <iostream>
#include <stdio.h>

using namespace std;

enum Color: bool {
	black = true,
	white = false
};

enum Piece_N : char{
	pawn = 'P',
	rook = 'R',
	knight = 'N',
	bishop = 'B',
	queen = 'Q',
	king = 'K',
	blank = 'X'
};

class Piece {
	private:
		bool alive;
		Color player;
		Piece_N name;
		unsigned int x, y;

		friend class Player;
	public:
		void setCoord(int, int);
		void setStatus(bool);
    	unsigned int getX() { return x; }
   	 	unsigned int getY() { return y; }
   	 	bool getStatus(){return alive;}
		Color getC(){return player;}
		Piece_N getN(){return name;}
		Piece(){}

};
struct NodeM{
	int x, y, xO, yO;
	bool check;
	NodeM *next;

	NodeM(int xOpos, int yOpos, int xPos, int yPos, bool b){
		xO = xOpos;
		yO = yOpos;
		x = xPos;
		y = yPos;
		check = b;
		this->next = NULL;
	}

	//the first node is used to store the amount of moves. we initialize y to -1 because if there were 0 moves and y was initialized to 0,
	//the print function would print 0,0 -- a legal board space.
	NodeM(){
		x = 0;
		y = -1;
		check = false;
		this->next = NULL;
	}

	NodeM *insertN(int xO, int yO, int xP, int yP, bool b){
		x++;
		NodeM *last = this, *current = next;
		while(current) {
			last = current;
			current = current->next;
		}
		last->next = new NodeM(xO, yO, xP, yP, b);
	}
};


class Player {
	private:
		Color color;
		Piece *pieces = new Piece[16];
		bool human;
	public:
		Piece *getPieceAt(int);
		Piece *getP(unsigned int, unsigned int);
		void setB(bool);
		bool getB(){return human;}
		Color getC(){return color;}
		void setC(Color);

};

class Square {
	private:
		Piece *piece;
		Color color;
	public:
		void setP(Piece *);
		void setC(Color);
		Piece *getP(){return piece;}
		Square(){}
};

Piece *findPiece(Player, Player, unsigned int, unsigned int);
pair<pair<Player*, Player*>,Square**>setup();
void printB(Square **);
void printNodeM(NodeM *);
bool searchNodeM(pair<int,int>, NodeM *);
pair <char,int> rParse(int,int);
#endif
