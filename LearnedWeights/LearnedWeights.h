#pragma once
#include<fstream>
#include<iostream>
using namespace std;

#include "Move.h"
#include "Board.h"
#include "Ju3..dge.h"

class learnedWeights
{
private:

	float opponent[4] = {0,0,1,0}; // oppnent's bingo,perm,rack, total score
	float agent[4] = {0,0,1,0};    //my bingo,perm,rack, total score
	int opp_moves,my_moves; // the number of moves of each player
	double Statistics[4];  // bingo,permium,rack,total # of steps
	double W[3];  //the learned weights

public:
	learnedWeights();
	~learnedWeights();
	void updateWeights(int winner);
	void newmove(int player,Move m,Board B, Bag bag, Judge j);
	int calculate_prem(Move m, Board B, Bag bag,string line);
	double* getWeights();

};
