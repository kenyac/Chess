#include "movep.hpp"



//takes starting coordinates and relative movement coordinates. then the max amount of times it can move in a turn (eg rook = across the board therefore 7)
NodeM *getMovesHelper(Player *p, int xPos, int yPos, int xMove, int yMove, int max, Square **board, NodeM *moves){
	int xO = xPos;
	int yO = yPos;
	for(int i = 0; i < max; i++){
		xPos += xMove;
		yPos += yMove;
		//cout << "X = " << xPos << '\t' << "Y = " << yPos << endl;
		if((xPos) >= 0 && (yPos) >= 0 && (xPos) < 8 && (yPos) < 8){
			//cout << endl << xPos << yPos;
			if(board[xPos][yPos].getP() == NULL){
				moves->insertN(xO, yO, xPos, yPos, false);
			}
			else if (board[xPos][yPos].getP()->getC() != p->getC()){
				if(board[xPos][yPos].getP()->getN() == 'K')
					moves->insertN(xO, yO, xPos, yPos, true); // this obviously won't be true when it's the player's turn, it is a post-move check check
				moves->insertN(xO, yO, xPos,yPos, false);
				break;
			}
			else{
				return moves;
			}
		}
		else{
			return moves;
		}
	}
	return moves;
}

NodeM *getMoves(Player *turn, char p, unsigned int x, unsigned int y, Square **board, NodeM *moves){
	switch(p){
		case 'R':
			getMovesHelper(turn, x, y, -1, 0, 7, board, moves); //O(x*n), where x is the possible directions. I will look for more optimal algorithms
			getMovesHelper(turn, x, y, 1, 0, 7, board, moves);
			getMovesHelper(turn, x, y, 0, -1, 7, board, moves);
			getMovesHelper(turn, x, y, 0, 1, 7, board, moves);
			break;
		case 'B':
			getMovesHelper(turn, x, y, 1, 1, 7, board, moves);
			getMovesHelper(turn, x, y, 1, -1, 7, board, moves);
			getMovesHelper(turn, x, y, -1, 1, 7, board, moves);
			getMovesHelper(turn, x, y, -1, -1, 7, board, moves);
			break;
		case 'N':
			getMovesHelper(turn, x, y, 1, 2, 1, board, moves);
			getMovesHelper(turn, x, y, 1, -2, 1, board, moves);
			getMovesHelper(turn, x, y, -1, 2, 1, board, moves);
			getMovesHelper(turn, x, y, -1, -2, 1, board, moves);
			getMovesHelper(turn, x, y, 2, 1, 1, board, moves);
			getMovesHelper(turn, x, y, 2, -1, 1, board, moves);
			getMovesHelper(turn, x, y, -2, 1, 1, board, moves);
			getMovesHelper(turn, x, y, -2, -1, 1, board, moves);
			break;
		case 'Q':
			getMovesHelper(turn, x, y, -1, 0, 7, board, moves);
			getMovesHelper(turn, x, y, 1, 0, 7, board, moves);
			getMovesHelper(turn, x, y, 0, -1, 7, board, moves);
			getMovesHelper(turn, x, y, 0, 1, 7, board, moves);
			getMovesHelper(turn, x, y, 1, 1, 7, board, moves);
			getMovesHelper(turn, x, y, 1, -1, 7, board, moves);
			getMovesHelper(turn, x, y, -1, 1, 7, board, moves);
			getMovesHelper(turn, x, y, -1, -1, 7, board, moves);
			break;
		case 'K':
			getMovesHelper(turn, x, y, -1, 0, 1, board, moves);
			getMovesHelper(turn, x, y, 1, 0, 1, board, moves);
			getMovesHelper(turn, x, y, 0, -1, 1, board, moves);
			getMovesHelper(turn, x, y, 0, 1, 1, board, moves);
			getMovesHelper(turn, x, y, 1, 1, 1, board, moves);
			getMovesHelper(turn, x, y, 1, -1, 1, board, moves);
			getMovesHelper(turn, x, y, -1, 1, 1, board, moves);
			getMovesHelper(turn, x, y, -1, -1, 1, board, moves);
			break;
		case 'P':
			if(turn->getC() == white){
				if(x == 6){
					getMovesHelper(turn, x, y, -1, 0, 2, board, moves);
				}
				else{
					getMovesHelper(turn, x, y, -1, 0, 1, board, moves);
				}

				if(y == 0){

					if(board[x-1][y+1].getP() != NULL){
						if(board[x-1][y+1].getP()->getC() != turn->getC()){
							getMovesHelper(turn, x, y, -1, 1, 1, board, moves);
						}
					}
				}
				else if (y == 7){
					if(board[x-1][y-1].getP() != NULL){
						if(board[x-1][y-1].getP()->getC() != turn->getC()){
							getMovesHelper(turn, x, y, -1, -1, 1, board, moves);
						}
					}
				}
				else if(board[x-1][y+1].getP() != NULL){
					if(board[x-1][y+1].getP()->getC() != turn->getC()){
						getMovesHelper(turn, x, y, -1, 1, 1, board, moves);
					}
				}
				else if(board[x-1][y-1].getP() != NULL){
					if(board[x-1][y-1].getP()->getC() != turn->getC()){
						getMovesHelper(turn, x, y, -1, -1, 1, board, moves);
					}
				}
			}
			else if(turn->getC() == black){
				if(x == 1){
					getMovesHelper(turn, x, y, 1, 0, 2, board, moves);
				}
				else{
					getMovesHelper(turn, x, y, 1, 0, 1, board, moves);
				}

				if(y == 0){
					if(board[x+1][y+1].getP() != NULL){
						if(board[x+1][y+1].getP()->getC() != turn->getC()){
							getMovesHelper(turn, x, y, 1, 1, 1, board, moves);
						}
					}
				}
				else if (y == 7){
					if(board[x+1][y-1].getP() != NULL){
						if(board[x+1][y-1].getP()->getC() != turn->getC()){
							getMovesHelper(turn, x, y, 1, -1, 1, board, moves);
						}
					}
				}
				else if(board[x+1][y+1].getP() != NULL){
					if(board[x+1][y+1].getP()->getC() != turn->getC()){
						getMovesHelper(turn, x, y, 1, 1, 1, board, moves);
					}
				}
				else if(board[x+1][y-1].getP() != NULL){
					if(board[x+1][y-1].getP()->getC() != turn->getC()){
						getMovesHelper(turn, x, y, 1, -1, 1, board, moves);
					}
				}
				break;
		}
	}
	return moves;
}

Square**moveToSquare(Player *attack, Player *defend, int xO, int yO, int x, int y, Square **board){
	board[x][y].setP(board[xO][yO].getP());
	board[xO][yO].setP(NULL);
	attack->getP(xO, yO)->setCoord(x, y);
	if(board[x][y].getP() != NULL){
		if(board[x][y].getP()->getC() == defend->getC())
			if(defend->getP(x, y)->getStatus()){
				defend->getP(x,y)->setStatus(false);
				defend->getP(x,y)->setCoord(8,8); //8,8 is the coordinate mark for dead pieces.
			}
	}
	//still need to add a revert move if the move does not deal with the enemy check.
}

NodeM *getTotalMoves(Player *p, Square **board){
	NodeM *tMoves = new NodeM;
	for(int i = 0; i < 16; i++){
		if(p->getPieceAt(i)->getX() < 8){ // alive check
		getMoves(p, p->getPieceAt(i)->getN(), p->getPieceAt(i)->getX(), p->getPieceAt(i)->getY(), board, tMoves);
		}
	}
}

NodeM *getRandNode(int i, NodeM *moves){
		NodeM *temp;
		temp = moves;
		int j = 0;
		while (temp != NULL){
			if(j == i){
				return temp;
			}
			j++;
			temp = temp->next;
		}
}

bool searchForCheck(NodeM *moves){
	NodeM *temp;
	temp = moves;
	while(temp != NULL){
		if(temp->check == true){
			return true;
		}
		temp = temp->next;
	}
	return false;
}
