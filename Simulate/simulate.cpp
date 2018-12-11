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



vector<Move> simualte::huristicMovesforEnd(Heuristic & heu, Board & board, Player & ana, Player & opponent, Bag b)
{
	heu.setBoard(board);
	heu.setBag(b);
	heu.setPlayer(ana);
	vector<Move> allMoves = heu.getAllMoves();
    heu.Slowendgame(allMoves,opponent.getTieStr());
	vector<Move>m;
	for (int i = 0; i < min(3, (int)allMoves.size());++i) {
		m.push_back(allMoves[i]);
	}
	return m;
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
Judge J;
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
				ret -= (ProbabilisticSearch(heu, idx + 1, board, 0, ana,
						opponent, bag, 0) + score);
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
Move simualte::nextPlay(Heuristic  heu, const vector<Move>& plays,
	const  Board & board, const Bag & bag, Player  ana, const Judge & j,
	Player & opponent, int d, SuperLeavesTrie superLeavesTrie){

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

	int idx = 0;
	int mx = -1e9;
	
	vector<Move>validPlays = superLeavesTrie.getBestN(plays, 40);
	for (int i = 0; i < validPlays.size(); ++i) {
		bagCopy = bag;
		boardCopy = board;
		anaCopy = ana;
		int  score = J.applyMove(validPlays[i], boardCopy, anaCopy, bagCopy);
		for (int k = 0; k < 1000; ++k) {

			score += ProbabilisticSearch(heu, 0, boardCopy, 1, anaCopy, opponentCopy, bagCopy, 0);
			bagCopy = bag;
			boardCopy = board;
			anaCopy = ana;
			opponentCopy = opponent;
		}
		if (mx < score) {
			mx = score;
			idx = i;
		}
	}
	return validPlays[idx];
}
/*
int simualte::simFinal2(Heuristic & heu, Board & board, bool game, Player ana, Player opponent, Bag & bag, int sc,int cnt )
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
			ret += simFinal2(heu, board, 0, ana,
				opponent, bag, sc, cnt + ex);
		}
		else if (move.tiles.size() > 0) {
			change(bag, opponent, move.tiles);
			ret += simFinal2(heu, board, 0, ana,
				opponent, bag, sc, 0);
		}
		else {
			int score = J.applyMove(move, board, opponent, bag);
			ret += simFinal2(heu,  board, 0, ana,
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
			ret += simFinal2(heu, board, 0, ana,
				opponent, bag, sc,cnt+ex);
		}
		else if (move.tiles.size() > 0) {
			change(bag, opponent, move.tiles);
			ret += simFinal2(heu, board, 0, ana,
				opponent, bag, sc,0);

		}
		else {
			int score = J.applyMove(move, board, ana, bag);
			ret += (simFinal2(heu, board, 1, ana,
				opponent, bag, score+sc,0) );
		}
	}

	return ret;
}

Move simualte::nextPlay(Heuristic  heu, const vector<Move>& plays,
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
int  valformove;
int mx = -1e9;
SuperLeavesTrie superLeavesTrie = SuperLeavesTrie();
vector<Move>validPlays = superLeavesTrie.getBestN(plays, 30);

for (int i = 0; i < validPlays.size(); ++i) {
valformove = 0;
bagCopy = bag;
boardCopy = board;
anaCopy = ana;
opponentCopy = opponent;
int  sc = J.applyMove(validPlays[i], boardCopy, anaCopy, bagCopy);
for (int k = 0; k < 1000; ++k) {
valformove += simFinal2(heu, boardCopy, 1, anaCopy, opponentCopy, bagCopy, score+sc,0);
bagCopy = bag;
boardCopy = board;
anaCopy = ana;
opponentCopy = opponent;
}
if (mx < valformove) {
mx = valformove;
idx = i;
}
}
return validPlays[idx];
}*/


int num;
int simualte::simulateALLPeg1(Heuristic & heu, Board & board, bool game, Player ana, Player opponent, int sc, int cnt,Bag bag)
{
	if (J.isClosed(board) || cnt >= 2) {	////////
		string myReack = ana.getTieStr();
		string hisReack = opponent.getTieStr();
		int rackScore = 0;
		for (int i = 0; i < myReack.length(); i++)
		{
			rackScore += bag.getTieScore(myReack[i] - 'A');
			rackScore -= bag.getTieScore(hisReack[i] - 'A');
		}
		num++;
		sc -= 2 * rackScore;
		
	 if (sc > 0)
			return 1;
	return 0;
		// mfrod azod 7aga hna huristic of board
	}
	int ret = 0;
	if (game == 1) {
		vector<Move>v = huristicMovesforEnd(heu, board, opponent, ana, bag);
		if (!(int)v.size()) {
			ret += simulateALLPeg1(heu, board, 0, ana, opponent, sc, cnt + 1, bag);
		}
		else {
			for (int w = 0; w < v.size(); ++w) {
				Board bb = board;
				Player opp = opponent;
				int score = J.applyMove(v[w], bb, opp, bag);
				ret += simulateALLPeg1(heu, bb, 0, ana, opp, sc-score, 0, bag);
			}
		}
	}
	else {
		vector<Move>v = huristicMovesforEnd(heu, board, ana,opponent, bag);
		if (!(int)v.size()) {
			ret += simulateALLPeg1(heu, board, 0, ana, opponent, sc, cnt + 1, bag);
		}
		else {
			for (int w = 0; w < v.size(); ++w) {
				Board bb = board;
				Player anacpp = ana;
				int score = J.applyMove(v[w], bb, anacpp, bag);
				ret += simulateALLPeg1(heu, bb, 0, anacpp, opponent, sc +score, 0, bag);
			}
		}		
	}
	return ret;
}
Move simualte::simualteForPEG1(int id,Bag bag,Board board,Player ana,Heuristic heu ,Judge judge,dictionary dec,Player p2) {
	vector<int>v;
	Player p(id);
	p.addScore(p2.getScore());
	for (int i = 0; i < 27; ++i) {
		if (bag.getTieCount(i)) {
			int j = bag.getTieCount(i);
			while (j--) {
				v.push_back(i);
				p.addTie(i);
			}
		}
	}
	float  mx = 1e-9;
		dec.execute(board,ana.getTieStr());
		Player anaCopy;
		Player opponentCopy;
		vector<Move>moves = dec.getVector();
		if (!moves.size()) {
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
		SuperLeavesTrie superLeavesTrie = SuperLeavesTrie();
		vector<Move>validPlays = superLeavesTrie.getBestN(moves, 30);
		for (int j = 0; j < validPlays.size(); ++j) {
			int valformove = 0;
			num = 0;
			Board bb = board;
			anaCopy = ana;
			int sc = judge.applyMove(validPlays[j], bb, anaCopy, bag);
			for (int i = 0; i < 8; ++i) {
				opponentCopy = p;
				opponentCopy.playTie(i);
				anaCopy.addTie(i);
				valformove += simulateALLPeg1( heu,  bb, 1, anaCopy,
					opponentCopy,sc+anaCopy.getScore()-opponentCopy.getScore(),0, bag);
				Board bb = board;
				anaCopy = ana;

			}
			if (valformove/1.0/num > mx) {
				mx = valformove / 1.0 / num;
				id = j;
			}
		}
		return validPlays[id];
}
/*Move simualte::simualteForPEG2(int id, Bag bag, Board board, Player ana, Heuristic heu, Judge judge, dictionary dec, Player p2) {
	vector<int>v;
	Player p(id);
	p.addScore(p2.getScore());
	for (int i = 0; i < 27; ++i) {
		if (bag.getTieCount(i)) {
			int j = bag.getTieCount(i);
			while (j--) {
				v.push_back(i);
				p.addTie(i);
			}
		}
	}
	float  mx = 1e-9;
	dec.execute(board, ana.getTieStr());
	Player anaCopy;
	Player opponentCopy;
	vector<Move>moves = dec.getVector();
	if (!moves.size()) {
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
	SuperLeavesTrie superLeavesTrie = SuperLeavesTrie();
	vector<Move>validPlays = superLeavesTrie.getBestN(moves, 30);
	for (int j = 0; j < validPlays.size(); ++j) {
		int valformove = 0;
		num = 0;
		Board bb = board;
		anaCopy = ana;
		int sc = judge.applyMove(validPlays[j], bb, anaCopy, bag);
		if (anaCopy.getTotalTies() <= 5) {
			for (int i = 0; i < 9; ++i) {
				for (int k = 0; k < 9; ++k) {
					if (i == k)
						continue;
					opponentCopy = p;
					opponentCopy.playTie(i);
					opponentCopy.playTie(k);
					anaCopy.addTie(i);
					anaCopy.addTie(k);
					valformove += simulateALLPeg1(heu, bb, 1, anaCopy,
						opponentCopy, sc + anaCopy.getScore() - opponentCopy.getScore(), 0, bag);
					Board bb = board;
					anaCopy = ana;
				}
			}
			if (valformove / 1.0 / num > mx) {
				mx = valformove / 1.0 / num;
				id = j;
			}
		}
	}
	else {
	
	
	
	}
	return validPlays[id];
}*/
