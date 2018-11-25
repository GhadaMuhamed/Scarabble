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
	word = "";
}

Move::Move(int x, int y, bool direction, string playedWord, string word) {
	switchMove = false;
	this->x = x;
	this->y = y;
	this->direction = direction;
	this->word = word;
	this->playedWord = playedWord;
}

