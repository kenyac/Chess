#include "initB.hpp"

Piece_N home_row[16] = {
pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
rook, knight, bishop, queen, king, bishop, knight, rook
};

void Piece::setStatus(bool b){
	alive = b;
}
void Piece::setCoord(int xC, int yC){
	x = xC;
	y = yC;
}
void Player::setC(Color c){
	color = c;
	if (c == white){
		for(int i = 0; i < 16; i++){
			pieces[i].alive = true;
			pieces[i].player = c;
			pieces[i].name = home_row[i];
			(i < 8)? pieces[i].x = 6 : pieces[i].x = 7;
			pieces[i].y = i % 8;
		}
	}
	else{
		for(int i = 0; i < 16; i++){
			pieces[i].alive = true;
			pieces[i].player = c;
			pieces[i].name = home_row[i];
			(i < 8)? pieces[i].x = 1 : pieces[i].x = 0;
			pieces[i].y = i % 8;
		}
	}
}

Piece *Player::getPieceAt(int i){
	return &pieces[i];
}
Piece *Player::getP(unsigned int x, unsigned int y){
	for(int i=0; i<16; i++)
        if(pieces[i].getX() == x && pieces[i].getY() == y)
            return &pieces[i];
    return NULL;
}

void Player::setB(bool b){
	human = b;
}

Piece *findPiece(Player h, Player c, unsigned int x, unsigned int y){
	if(h.getP(x,y) != NULL){
		return h.getP(x,y);
	}
	else if(c.getP(x,y) != NULL){
		return c.getP(x,y);
	}
	else{
		///cout << "returning NULL" << endl;
		return NULL;
	}
}

void Square::setP(Piece *p){
	piece = p;
}
void Square::setC(Color c){
	color = c;
}
pair<pair<Player*, Player*>,Square**>setup(){

	char side;
	cout << "Which side would you like to be? (B/W): ";
	cin >> side;
	cout << endl;
	Player *human = new Player;
	Player *cpu = new Player;
	if(toupper(side) == 'W'){
		human->setC(white);
		cpu->setC(black);
	}
	else if(toupper(side) == 'B'){
		human->setC(black);
		cpu->setC(white);
	}
	else
		cout << "Invalid input";

	human->setB(true);
	cpu->setB(false);

	Square **board = new Square *[8];
	for(int i = 0; i < 8; i++){
		board[i] = new Square [8];
	}

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			//cout << i*j << endl;
			((i + j) % 2)? board[i][j].setC(white) : board[i][j].setC(black);
			board[i][j].setP(findPiece(*human,*cpu,i,j));
		}
	}
	return make_pair(make_pair(human, cpu), board);
}

void printB(Square **board){
	for(int i = 0; i < 8; i++){
		cout << (8 - i) << '\t';
		for(int j = 0; j < 8; j++){
			if(board[i][j].getP() == NULL){
				printf("%c\t", blank);
			}
			else{
				printf("%c\t",board[i][j].getP()->getN());
			}
		}
		cout << endl;
	}
	cout << "\tA\tB\tC\tD\tE\tF\tG\tH" << endl;
}

void printNodeM(NodeM *moves){
	pair <char,int> pMoves;
	if(moves == NULL){
		cout << "No available moves for selected piece." << endl;
	}
	else{
		NodeM *temp;
		temp = moves;
		while(temp != NULL){
			if(temp->y != -1){
				pMoves = rParse(temp->x,temp->y);
				cout << pMoves.first<< pMoves.second << " ";
			}
			else {
				//cout << temp->x << " " << temp->y << endl;
			}
			temp = temp->next;
		}
	}
	cout << endl;
}

bool searchNodeM(pair<int,int> sMove, NodeM *moves){
	NodeM *temp;
	temp = moves;
	while(temp != NULL){
		if(sMove.first == temp->x && sMove.second == temp->y){
			return true;
		}
		temp = temp->next;
	}
	return false;
}
pair<char,int> rParse(int x, int y){
	return make_pair(y + 'A',(8-x));
}
