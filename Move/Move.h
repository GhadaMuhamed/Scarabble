/*
* Move.h
*
*  Created on: Nov 25, 2018
*      Author: ghada
*/

#ifndef MOVE_MOVE_H_
#define MOVE_MOVE_H_


#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<string>
#include <sstream>
using namespace std;
struct Move {
	string word, playedWord;
	int x, y;
	double heuristicValue;
	bool direction;
	bool switchMove;
	vector<char> tiles;
	Move();
    Move(int x, int y, bool direction, const string& playedWord, const string& word);
    friend bool operator<(const Move move1, const Move move2);
};



#endif /* MOVE_MOVE_H_ */