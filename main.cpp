#include <iostream>
#include "Bag/Bag.h"
#include "Board/Board.h"
#include "Player/Player.h"
#include "Judge/Judge.h"
#include "Dictionary/dictionary.h"

int main() {
	Bag bag1 = Bag();
	Bag bag2 = Bag();
	dictionary d("sowpods.txt");
	Board board = Board();
	board.initBoard();
	cout << board;
	cout << "----------------------------------------------\n";
	cout << bag1;
	cout << "----------------------------------------------\n";

	Player player1 = Player(1);
	int rand_7[7] = { 2, 3, 6, 19, 'R' - 'A', 'I' - 'A', 26 };
	for (int i : rand_7) {
		bag1.removeTie(i);
		if (!player1.addTie(i))
			cout << "How false?";
	}
	cout << player1;
	cout << "----------------------------------------------\n";
	board.applyMove(7, 5, 'P'-'A');
	board.applyMove(7, 6, 'L'-'A');
	board.applyMove(7, 8, 'Y'-'A');
	cout << board;
	cout << "----------------------------------------------\n";
    Judge judge = Judge();
    Move move;
    move.playedWord = "RIHAM";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    cout << judge.applyMove(move, board, player1, bag1) << endl << endl;
//    int posX, posY; char tieChar;
//    while (true) {
//        cout << "Please, Enter the position you want play (X, Y) and the tie value. your current info is: ";
//        cout << player1;
//        cout << "If you want to Exit put -1\n\n";
//        cin >> posX;
//        if (posX == -1) break;
//        cin >> posY >> tieChar;
//        int tie = int(tieChar-'A');
//        if (player1.playTie(tie)) {
//            if (board.putTie(posX, posY, tie)) {
//                cout << "Tie has been put successfully on the board\n";
//                cout << board;
//                cout << "----------------------------------------------\n";
//            } else {
//                cout << "Please make sure that the current position is aligned to a tie\n";
//            }
//        } else {
//            cout << "Please make sure that this tie already exists on you bag!\n";
//        }
//    }

	cout << board;
	return 0;
}
