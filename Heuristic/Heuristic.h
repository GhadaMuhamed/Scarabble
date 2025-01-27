/*
 * Heuristic.h
 *
 *  Created on: Nov 25, 2018
 *      Author: ghada
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include<cmath>
#include <algorithm>
#include "../Dictionary/dictionary.h"
#include "../Judge/Judge.h"

using namespace std;
#ifndef HEURISTIC_H_
#define HEURISTIC_H_

class Heuristic {
	Board* board;
	dictionary* dec;
	Bag* bag;
	Player* player;
	Player* opponent;

	Judge* J;
	const char st = 'A';
	const string mostUsedLetters = "etaoinshrdlcumwfgypbvkjxqz";
	int state;
	map<char, double> L1, L2;
	double w[5];
	double startW[5];
public:
	Heuristic(Board&, dictionary&, Bag&, Judge&, Player&, Player&);
	vector<pair<string, int>> getPossibleBingo(string str, int cut[]);
	pair<bool, pair<int, int> > filterPossibles(string& s, int cur[]);
	double calcProbability(int freq[], int score, int cur[]);
	double expectedBingoMe(Move& move);
	double expectedBingoOpponent();
	double RackLeaveScore(string C);
	void getChange(char*);
	void setBoard(Board& b);
	void setBag(Bag& b);
	void setPlayer(Player& p);
	double qSticking(Move&);

	double QwithU(string m);
	double getHeu(Move& m);
	vector<Move> getAllMoves();
	double DefensiveStrategy(Move move);
	//void Slowendgame(vector<Move>& possibleMoves, string oPPrack);

	virtual ~Heuristic();
};

#endif /* HEURISTIC_H_ */

