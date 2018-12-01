/*
* Move.cpp
*
*  Created on: Nov 5, 2018
*      Author: ghada
*/

#include "Move.h"

Move::Move() {
	// TODO Auto-generated constructor stub
	switchMove = direction = false;
	x = y = 0;
	heuristicValue = 0.0;
	word = "";
}

Move::Move(int x, int y, bool direction, const string& playedWord, const string& word) {
	switchMove = false;
	this->x = x;
	this->y = y;
	this->heuristicValue = 0.0;
	this->direction = direction;
	this->word = word;
	this->playedWord = playedWord;
}

bool operator< (const Move move1, const Move move2) {
    return move1.heuristicValue > move2.heuristicValue;
}
