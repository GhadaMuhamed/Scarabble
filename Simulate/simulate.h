#pragma once

#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<string>
#include <sstream>
#include"../Judge/Judge.h"
#include "../Heuristic/Heuristic.h"
#include "../Dictionary/dictionary.h"
#include "../SuperLeavesTrie/SuperLeavesTrie.h"
using namespace std;
class  simualte {
	int depth;
    Judge J;
public:
	Move huristicMoves(Heuristic &heu, Board &board, Player &ana, Player &opponent,
					   Bag b);

	void radom_rack(Bag &bag, Player &opponent);

	void change(Bag &bag, Player &ply, vector<char> tiles);

	int ProbabilisticSearch(Heuristic &heu, int idx, Board &board,
							bool game, Player ana, Player opponent, Bag &bag, int cnt);

	Move nextPlay(Heuristic  heu, const vector<Move>& plays,
				  const  Board & board, const Bag & bag,  Player&  ana, const Judge & j,
				  Player& opponent,int d);

	int simFinal2(Heuristic &heu, int idx, Board &board, bool game, Player ana, Player opponent, Bag &bag, int score,
				  int cnt);

};