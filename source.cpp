#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include <sstream>
#include <time.h>
#include "Heuristic/Heuristic.h"
#include "Dictionary/dictionary.h"
#include "Judge/Judge.h"

using namespace std;

# define depth 10
# define S 10
Judge J;
dictionary dec;
//Heuristic heu;
Move huristicMoves(Heuristic& heu, Board& board, Player& ana, Player& opponent,
		Bag b) {
	string C;
	heu.setBoard(board);
	heu.setBag(b);
	heu.setPlayer(ana);
	vector<Move> allMoves = heu.getAllMoves();
	Move BestMove;
	int mx = -1;

	for (int i = 0; i < allMoves.size(); ++i) {
		float num = heu.getHeu(allMoves[i]);
		if (num > mx)
			mx = num, BestMove = allMoves[i];
		heu.setBoard(board);
		heu.setBag(b);
		heu.setPlayer(ana);
	}
	return BestMove;
}
long double radom_rack(Bag & bag, Player & opponent) {
	long double p = 1.0;
	srand(time(NULL));
	int tot = bag.bagLen();
	while (opponent.getTotalTies() < 7 && tot) {	////// for omnia
		int r = rand() % 27;
		while (!bag.getTieCount(r)) {	//// for omnia
			r = rand() % 27;
		}
		p = p * (bag.getTieCount(r) * 1.0 / tot);	/////for omnia
		bag.removeTie(r);
		tot--;
		opponent.addTie(r);
	}
	return p;
}
long double change(Bag & bag, Player & ply, vector<char> tiles) {
	long double p = 1.0;
	srand(time(NULL));
	int tot = bag.bagLen();
	for (int i = 0; i < tiles.size(); ++i) {
		int r = rand() % 27;
		while (!bag.getTieCount(r)) {	//// for omnia
			r = rand() % 27;
		}
		bag.removeTie(r);
		p *= bag.getTieCount(r) * 1.0 / tot;
		tot--;
		ply.addTie(r);
	}
	for (int i = 0; i < tiles.size(); ++i) {
		bag.addTie((int) (tiles[i] - 'A'));
	}
	return p;
}
long double huristicBoard(Board &b) {
	return 0.0;
}
long double ProbabilisticSearch(Heuristic& heu, int idx, Board & board,
		bool game, Player ana, Player opponent, Bag & bag, int cnt) {
	if (J.isClosed(board) || idx >= depth || cnt >= 2) {	////////
		return huristicBoard(board);
		// mfrod azod 7aga hna huristic of board
	}
	long double ret = 0;
	Bag b = bag;
	for (int i = 0; i < S; ++i) {
		long double p;
		b = bag;	// check for riham operator overloding
		if (game == 1) {
			p = radom_rack(b, opponent);
			Move move = huristicMoves(heu, board, opponent, ana, b);
			if (move.switchMove) {
				bool ex = false;
				if (bag.bagLen() == 0)
					ex = true;
				ret -= p
						* ProbabilisticSearch(heu, idx + 1, board, 0, ana,
								opponent, b, cnt + ex);
			} else if (move.tiles.size() > 0) {
				p = change(b, opponent, move.tiles);
				ret -= p
						* ProbabilisticSearch(heu, idx + 1, board, 0, ana,
								opponent, b, 0);
			} else {
				int score = J.applyMove(move, board, opponent, b);
				ret -= p
						* (ProbabilisticSearch(heu, idx + 1, board, 0, ana,
								opponent, b, 0) + score);
			}
		} else {
			p = radom_rack(b, ana);
			Move move = huristicMoves(heu, board, ana, opponent, b);
			if (move.switchMove) {
				bool ex = false;
				if (bag.bagLen() == 0)
					ex = true;
				ret += p
						* ProbabilisticSearch(heu, idx + 1, board, 0, ana,
								opponent, b, cnt + ex);
			} else if (move.tiles.size() > 0) {
				p = change(b, opponent, move.tiles);
				ret += p
						* ProbabilisticSearch(heu, idx + 1, board, 0, ana,
								opponent, b, 0);

			} else {
				int score = J.applyMove(move, board, ana, b);
				ret += p
						* (ProbabilisticSearch(heu, idx + 1, board, 1, ana,
								opponent, b, 0) + score);
			}
		}

	}
	return ret;
}

// ana mb3otly acctions klaha tnf3 tt3ml rihaaaaaaaaaaaaaaaaaam
Move nextPlay(Heuristic& heu, const vector<Move>&plays, Board board, Bag bag,
		Player ana, Judge j) {
	if (!plays.size()) {
		Move m;
		heu.setPlayer(ana);
		char* ex = new char[7];
		heu.getChange(ex);
		if (strlen(ex) == 0)
			m.switchMove = true;
		for (int i = 0; i < strlen(ex); ++i)
			m.tiles.push_back(ex[i]);
		return m;
	}
	long double mx = -1e18;
	int playIdx = 0;
	J = j;
	int size = plays.size();
	for (int i = 0; i < plays.size(); ++i) {
		int score = J.applyMove(plays[i], board, ana, bag);
		Player opponent(2);	/////for omnia
		// 1 for opponent ,0 for me
		long double expectedValue = ProbabilisticSearch(heu, 0, board, 1, ana,
				opponent, bag, 0) + score / 1.0 / size;
		if (mx < expectedValue) {
			mx = expectedValue;
			playIdx = i;
		}
	}
	return plays[playIdx];
}
