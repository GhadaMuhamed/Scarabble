#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include <sstream>
#include<time.h>
#include "../Heuristic/Heuristic.h"
#include "../Judge/Judge.h"
#include "simulate.h"

using namespace std;

Move simualte::huristicMoves(Heuristic & heu, Board & board, Player & ana, Player & opponent, Bag b)
{
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

void  simualte::radom_rack(Bag & bag, Player & opponent)
{
	srand(time(NULL));
	int tot = bag.bagLen();
	while (opponent.getTotalTies() < 7 && tot) {	////// for omnia
		int r = rand() % 27;
		while (!bag.getTieCount(r)) {	//// for omnia
			r = rand() % 27;
		}
		bag.removeTie(r);
		tot--;
		opponent.addTie(r);
	}
}

void simualte::change(Bag & bag, Player & ply, vector<char> tiles) {

	srand(time(NULL));
	int tot = bag.bagLen();
	for (int i = 0; i < tiles.size(); ++i) {
		int r = rand() % 27;
		while (!bag.getTieCount(r)) {	
			r = rand() % 27;
		}
		bag.removeTie(r);
		tot--;
		ply.addTie(r);
	}
	for (char tile : tiles) {
		bag.addTie((int)(tile - 'A'));
	}
}
int simualte::ProbabilisticSearch(Heuristic & heu, int idx, Board & board, bool game, Player ana, Player opponent, Bag & bag, int cnt)
{
	if (J.isClosed(board) || idx >= depth || cnt >= 2) {	////////
		return 0;
		// mfrod azod 7aga hna huristic of board
	}
	int ret = 0;
	if (game == 1) {

		radom_rack(bag, opponent);
		Move move = huristicMoves(heu, board, opponent, ana, bag);
		if (move.switchMove) {
			bool ex = false;
			if (bag.bagLen() == 0)
				ex = true;
				ret -= ProbabilisticSearch(heu, idx + 1, board, 0, ana,
						opponent, bag, cnt + ex);
			}
			else if (move.tiles.size() > 0) {
				change(bag, opponent, move.tiles);
				ret -=ProbabilisticSearch(heu, idx + 1, board, 0, ana,
						opponent, bag, 0);
			}
			else {
				int score = J.applyMove(move, board, opponent, bag);
				ret -= ProbabilisticSearch(heu, idx + 1, board, 0, ana,
						opponent, bag, 0) + score;
			}
		}
		else {
			 radom_rack(bag, ana);
			Move move = huristicMoves(heu, board, ana, opponent, bag);
			if (move.switchMove) {
				bool ex = false;
				if (bag.bagLen() == 0)
					ex = true;
				ret += ProbabilisticSearch(heu, idx + 1, board, 0, ana,
						opponent, bag, cnt + ex);
			}
			else if (move.tiles.size() > 0) {
				change(bag, opponent, move.tiles);
				ret +=  ProbabilisticSearch(heu, idx + 1, board, 0, ana,
						opponent, bag, 0);

			}
			else {
				int score = J.applyMove(move, board, ana, bag);
				ret += (ProbabilisticSearch(heu, idx + 1, board, 1, ana,
						opponent, bag, 0) + score);
			}
		}

	return ret;
}

int simualte::simFinal2(Heuristic & heu, int idx, Board & board, bool game, Player ana, Player opponent, Bag & bag, int sc,int cnt )
{
	if (J.isClosed(board)||cnt>=2) {	////////
		string myReack = ana.getTieStr();
		string hisReack = opponent.getTieStr();
		int rackScore = 0;
		for (int i = 0; i < myReack.length(); i++)
		{
			rackScore += bag.getTieScore(myReack[i] - 'A');
			rackScore -= bag.getTieScore(hisReack[i] - 'A');
		}
		sc -= 2 * rackScore;
		if (sc < 0)
			return -1;
		else if (sc > 0)
			return 1;
		return 0;
		// mfrod azod 7aga hna huristic of board
	}
	int ret = 0;
	if (game == 1) {
		radom_rack(bag, opponent);
		Move move = huristicMoves(heu, board, opponent, ana, bag);
		if (move.switchMove) {
			bool ex = false;
			if (bag.bagLen() == 0)
				ex = true;
			ret += simFinal2(heu, idx + 1, board, 0, ana,
				opponent, bag, sc, cnt + ex);
		}
		else if (move.tiles.size() > 0) {
			change(bag, opponent, move.tiles);
			ret += simFinal2(heu, idx + 1, board, 0, ana,
				opponent, bag, sc, 0);
		}
		else {
			int score = J.applyMove(move, board, opponent, bag);
			ret += simFinal2(heu, idx + 1, board, 0, ana,
				opponent, bag, sc + score, 0);
		}
	}
	else {
		radom_rack(bag, ana);
		Move move = huristicMoves(heu, board, ana, opponent, bag);
		if (move.switchMove) {
			bool ex = false;
			if (bag.bagLen() == 0)
				ex = true;
			ret += simFinal2(heu, idx + 1, board, 0, ana,
				opponent, bag, sc,cnt+ex);
		}
		else if (move.tiles.size() > 0) {
			change(bag, opponent, move.tiles);
			ret += simFinal2(heu, idx + 1, board, 0, ana,
				opponent, bag, sc,0);

		}
		else {
			int score = J.applyMove(move, board, ana, bag);
			ret += (simFinal2(heu, idx + 1, board, 1, ana,
				opponent, bag, score+sc,0) );
		}
	}

	return ret;
}

Move simualte::nextPlay(  Heuristic  heu, const vector<Move>& plays,
						  const  Board & board, const Bag & bag,  Player&  ana, const Judge & j,
						  Player & opponent,int d)
{

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
	depth = d;
	Player anaCopy(ana.getPlayerID());
	Player  opponentCopy(opponent.getPlayerID());
	Bag bagCopy = bag;
	Board boardCopy = board;
	anaCopy.addScore(ana.getScore());
    anaCopy.setTotalTies(ana.getTotalTies());
	int idx = 0;
	double mx = -1e9;
	opponentCopy.putScore(opponent.getScore());
    opponentCopy.setTotalTies(opponent.getTotalTies());
	for (int i = 0; i < plays.size(); ++i) {
		for (int k = 0; k < 27; ++k) {
			anaCopy.addValue(ana.getValue(k), k);
		}
		for (int k = 0; k < 27; ++k) {
			opponentCopy.addValue(opponent.getValue(k), k);
		}
		boardCopy = board;
		bagCopy = bag;

		float  score = J.applyMove(plays[i], boardCopy, anaCopy, bagCopy);
		for (int k = 0; k < 1000; ++k) {
			score += ProbabilisticSearch(heu, 0, boardCopy, 1, anaCopy, opponentCopy, bagCopy, 0);
            bagCopy = bag;
            boardCopy = board;
            for (int k = 0; k < 27; ++k) {
                anaCopy.addValue(ana.getValue(k), k);
            }
            for (int k = 0; k < 27; ++k) {
                opponentCopy.addValue(opponent.getValue(k), k);
            }
            anaCopy.addScore(ana.getScore());
            anaCopy.setTotalTies(ana.getTotalTies());
            opponentCopy.putScore(opponent.getScore());
            opponentCopy.setTotalTies(opponent.getTotalTies());
		}
		if (mx < score) {
			mx = score;
			idx = i;
		}
	}
	return plays[idx];
}
/*Move simualte::nextPlay(Heuristic  heu, const vector<Move>& plays,
	const  Board & board, const Bag & bag, Player  ana, const Judge & j,
	const Player & opponent, int score)
{

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
	Player anaCopy(ana.getPlayerID());
	Player  opponentCopy(opponent.getPlayerID());
	Bag bagCopy = bag;
	Board boardCopy = board;
	int size = (int)plays.size();
	int idx = 0;
	float mx = -1e9;
	SuperLeavesTrie superLeavesTrie = SuperLeavesTrie();
	vector<Move>validPlays = superLeavesTrie.getBestN(plays, 30);

	for (int i = 0; i < validPlays.size(); ++i) {
		for (int i = 0; i < 27; ++i) {
			anaCopy.addValue(ana.getValue(i), i);
		}
		for (int i = 0; i < 27; ++i) {
			opponentCopy.addValue(opponent.getValue(i), i);
		}
		boardCopy = board;
		bagCopy = bag;
		float  score = J.applyMove(validPlays[i], boardCopy, anaCopy, bagCopy);
		for (int k = 0; k < 1000; ++k) {
			score += simFinal2(heu, 0, boardCopy, 1, anaCopy, opponentCopy, bagCopy, score,0);

		}
		if (mx < score) {
			mx = score;
			idx = i;
		}
	}
	return validPlays[idx];
}*/