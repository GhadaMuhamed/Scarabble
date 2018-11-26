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

using namespace std;
#ifndef HEURISTIC_H_
#define HEURISTIC_H_

class Heuristic {
	Board board;
	dictionary dec;
	Bag bag;
	Judge J;
	const char st = 'A';
	const string mostUsedLetters = "etaoinshrdlcumwfgypbvkjxqz";

public:
	Heuristic(Board, dictionary, Bag, Judge);
	vector<pair<string, int>> getPossibleBingo(string str,int cut[]);
	bool filterPossibles(string s, int cur[]);
	double calcProbability(int freq[], int score, int cur[]);
	double expectedBingoMe(string s, Player &player);
	double expectedBingoOpponent();
	double RackLeaveScore(string C);
	char getChange(Player& p);
	void setBoard(Board b);
	void setBag(Bag b);
	vector<Move> getAllMoves();
	double DefensiveStrategy(Move move);

	virtual ~Heuristic();
};

#endif /* HEURISTIC_H_ */
