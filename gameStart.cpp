#include "gameStart.hpp"

pair<int, int> parse(string p){
	if(p.length() != 2){
		//these will have error messages in the future
		cout << "Invlaid1" << endl;
	}
	else if(toupper(p[0]) < 65 || toupper(p[0]) > 72){
		cout << "Invlaid2" << endl;
	}


	else if((p[1] - '0') < 1 || (p[1] - '0') > 8){
		cout << "Invalid3" << endl;
	}
	else{
		int col;
		switch(toupper(p[0])){
			case 'A':
				col = 0;
				break;
			case 'B':
				col = 1;
				break;
			case 'C':
				col = 2;
				break;
			case 'D':
				col = 3;
				break;
			case 'E':
				col = 4;
				break;
			case 'F':
				col = 5;
				break;
			case 'G':
				col = 6;
				break;
			case 'H':
				col = 7;
				break;
			default:
				cout << "Invalid4" << endl;
				break;
		}
		return make_pair( 8 - (p[1] - '0'), col);
	}
}

void player_turn(Player *human, Player *cpu, Square **board, string *condition){
	NodeM *moves = new NodeM;
	string moveS, moveD;
	pair<int,int> start, dest;
	cout << "Select a piece to move: ";
	cin >> moveS;
	start = parse(moveS);
	if(board[start.first][start.second].getP() != NULL && board[start.first][start.second].getP()->getC() == human->getC() && human->getP(start.first, start.second)->getStatus()){
	//	cout << "valid move";

		printNodeM(getMoves(human, board[start.first][start.second].getP()->getN(), start.first, start.second, board, moves));
		cout << "Move piece to? : ";
		cin >> moveD;
		dest = parse(moveD);
		if(searchNodeM(dest, moves)){
			cout << "accepted" << endl;
			moveToSquare(human, cpu, start.first, start.second, dest.first, dest.second, board);
			system("CLS");
			printB(board);
			turn(cpu, human, board, *condition);
		}

	}

}

void cpu_turn(Player *cpu, Player *human, Square **board, string *condition){
	system("CLS");
	char cont;
	NodeM *tMoves = getTotalMoves(cpu, board);
	//printNodeM(tMoves);
	NodeM *rMove = getRandNode(rand() % tMoves->x + 1, tMoves);
	moveToSquare(cpu, human, rMove->xO, rMove->yO, rMove->x, rMove->y, board);
	printB(board);
	cout << rParse(rMove->xO, rMove->yO).first << rParse(rMove->xO, rMove->yO).second << " to: " << rParse(rMove->x, rMove->y).first << rParse(rMove->x, rMove->y).second << endl;
	//cin >> cont;
	turn(human, cpu, board, *condition);
}

void turn(Player *attack, Player *defend, Square **board, string condition){//condition is for the defending player
	if(condition == "Checkmate"){
		return;
	}
	else if(attack->getB() == true){
		cout << "Player turn" << endl;
		player_turn(attack, defend, board, &condition);
	}
	else{
		//cout << "Computer turn" << endl;
		cpu_turn(attack, defend, board, &condition);
	}
}
void startGame(pair<pair<Player*, Player*>,Square**> start_state){
	srand(time(NULL));
	if(start_state.first.first->getC() == white){
		printB(start_state.second);
		//cout << "Player color is white" << endl;
		turn(start_state.first.first, start_state.first.second, start_state.second, "");
	}
	else{
		//cout << "Player color is black" << endl;
		turn(start_state.first.second, start_state.first.first, start_state.second, "");
	}

}
