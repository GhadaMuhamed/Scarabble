#include <iostream>
#include "SuperLeavesTrie/SuperLeavesTrie.h"
#include "Bag/Bag.h"
#include "Board/Board.h"
#include "Player/Player.h"
#include "Judge/Judge.h"
#include "Simulate/simulate.h"
#include "Bstar/Bstar.h"
#include "Heuristic/Heuristic.h"
#include "Dictionary/dictionary.h"

void random_rack(Bag& bag, Player& player) {
	// set random rack for each player
	while (player.getTotalTies() < 7 && bag.bagLen() > 0) {
		int cur_rand = int((rand() / (RAND_MAX + 1.0)) * 27);
		while (bag.getTieCount(cur_rand) == 0) {
			cur_rand = int((rand() / (RAND_MAX + 1.0)) * 27);
		}
		bag.removeTie(cur_rand);
		player.addTie(cur_rand);
	}
}
Move appropriateSimulation(Board& board, dictionary& dic, Player players[2], int turn, simualte& sim, Heuristic& heu,
						   Judge  j, Bstar bstar,Bag & bag, vector<Move> &availableMoves, SuperLeavesTrie superLeavesTrie) {
	Player p(1 - turn);
	p.addScore(players[1 - turn].getScore());

	if (bag.bagLen() <=7) {
		node n = bstar.b_star(availableMoves,board,players[turn],p,bag,dic/*,heu*/);
		return n.mv;
	}
	else if (bag.bagLen() == 8) {
		return sim.simualteForPEG1(turn, bag, board, players[turn], heu, j, dic, p);
	}

	else {
		return sim.nextPlay(heu, availableMoves, board, bag, players[turn], j, p, 3, superLeavesTrie);
	}
}

int main() {
	Board board = Board();
	Bag bag = Bag();
	Player players[] = { Player(0), Player(1) };
	simualte sim = simualte();
	Bstar bstar = Bstar();
	dictionary dic = dictionary("sowpods.txt");
	Judge judge = Judge();
	Heuristic heu = Heuristic(board, dic, bag, judge, players[0], players[1]);
	SuperLeavesTrie superLeavesTrie = SuperLeavesTrie();
	int turn = 0;
	int pass = 0;
	cout << "dsadad" << endl;
	random_rack(bag, players[turn]);
	string rack = players[turn].getTieStr();
	board.putFirstTie(rack[0] - 'A');
	rack.erase(rack.begin(), rack.begin() + 1);
	cout << rack << endl;
	while (true)
	{
		dic.execute(board, rack, 3);
		vector<Move> moves = dic.getVector();
		Move m = appropriateSimulation(board, dic, players, turn, sim, heu, judge, bstar, bag, moves, superLeavesTrie);
		if (m.switchMove) pass++;
		else
			pass = 0;

		if (pass == 2) break;

		if (m.tiles.size() == 0)
			players[turn].addScore( judge.applyMove(m, board, players[turn], bag) );
		else {
			for (int i = 0; i < m.tiles.size(); i++)
			{
				players[turn].playTie(m.tiles[i] - 'A');
			}
			random_rack(bag, players[turn]);
		}
		cout << board;
		cout << players[turn];
		cout << players[1-turn];

		if (judge.isClosed(board))  break;

		turn = 1 - turn;
		random_rack(bag, players[turn]);
		rack = players[turn].getTieStr();
	}

	return 0;
}