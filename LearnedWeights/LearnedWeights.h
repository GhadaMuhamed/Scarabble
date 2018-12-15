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


  struct Point{ int r,c; };
	float opponent[4] = {0,0,1,0}; // oppnent's bingo,perm,rack, total score
	float agent[4] = {0,0,1,0};    //my bingo,perm,rack, total score
	int opp_moves,my_moves; // the number of moves of each player
	double Statistics[4];  // bingo,permium,rack,total # of steps
	double W[3];  //the learned weights

public:
	learnedWeights();
	~learnedWeights();
	void updateWeights(int winner);
	void newmove(vector<Point> positions,int player,int total_score,Move m,Board B, Bag bag, Judge j);
	int calculate_prem(vector<Point> positions, Board B, Bag bag);
	double* getWeights();

};
