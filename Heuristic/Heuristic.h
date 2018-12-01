/*
 * Heuristic.h
 *
 *  Created on: Nov 25, 2018
 *      Author: ghada
 */
#include<bits/stdc++.h>
#include "../Board/Board.h"
#include "../Dictionary/dictionary.h"
#include "../Bag/Bag.h"
#include "../Judge/Judge.h"
#include "../Player/Player.h"

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
	map<char,double>L1,L2;
public:
	Heuristic(Board&, dictionary&, Bag&, Judge&,Player&,Player&);
	vector<pair<string, int>> getPossibleBingo(string str, int cut[]);
	bool filterPossibles(string s, int cur[]);
	double calcProbability(int freq[], int score, int cur[]);
	double expectedBingoMe(Move& move);
	double expectedBingoOpponent();
	double RackLeaveScore(string C);
	void getChange(char*);
	void setBoard(Board& b);
	void setBag(Bag& b);
	void setPlayer(Player& p);
	void qSticking(vector<Move>& vec);

	double QwithU(string m);
	double getHeu(Move& m);
	vector<Move> getAllMoves();
	double DefensiveStrategy(Move move);

	virtual ~Heuristic();
};

#endif /* HEURISTIC_H_ */
