#include <iostream>
#include "SuperLeavesTrie/SuperLeavesTrie.h"
#include "Bag/Bag.h"
#include "Board/Board.h"
#include "Player/Player.h"
#include "Judge/Judge.h"
#include "Dictionary/dictionary.h"

int main() {
    SuperLeavesTrie superLeavesTrie = SuperLeavesTrie();


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
    int rand_7[3] = { 'E' - 'A', 'Q' - 'A', 'Z' - 'A' };
    for (int i : rand_7) {
        bag1.removeTie(i);
        if (!player1.addTie(i)) {
            cout << "How false?";
        }
    }
    cout << player1;
    cout << "Heuristic Player: " << superLeavesTrie.getFromHeuristic(player1) << endl;
    cout << "----------------------------------------------\n";
	board.applyMove(7, 5, 'P'-'A');
	board.applyMove(7, 6, 'L'-'A');
	board.applyMove(7, 8, 'Y'-'A');
	cout << board;
	cout << "----------------------------------------------\n";
    Judge judge;
    vector<Move> moves;
    Move move;
    move.playedWord = "RIHAM";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GVAZA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GMN";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHFX";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GFG";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GFV";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "G";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHS";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "DA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "EDA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "ADHADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "XHADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "AGHAZA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "DHADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHDADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHADEA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHWADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "RHADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "AADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHADAZ";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GXHADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHCADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHAMDA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHEADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GWHADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "WHADAS";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "HAADA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move.playedWord = "GHASDA";
    move.direction = true;
    move.switchMove = false;
    move.x = 4;
    move.y = 7;
    moves.push_back(move);
    move = superLeavesTrie.getBest(moves);
    cout << move.playedWord << " " << move.heuristicValue << endl;
    moves = superLeavesTrie.getBest23(moves);
    cout << moves.back().playedWord << " " << moves.back().heuristicValue << endl;
    cout << moves.front().playedWord << " " << moves.front().heuristicValue << endl;
//    cout << judge.applyMove(move, board, player1, bag1) << endl << endl;
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
