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

public:
	Move huristicMoves(Heuristic& heu, Board& board, Player& ana, Player& opponent,
		Bag b);
	void  radom_rack(Bag & bag, Player & opponent);

	void change(Bag & bag, Player & ply, vector<char> tiles);
	int ProbabilisticSearch(Heuristic& heu, int idx, Board & board,
	bool game, Player ana, Player opponent, Bag & bag, int cnt);
	Move nextPlay( Heuristic  heu, const vector<Move>& plays,
		const  Board & board, const Bag & bag,  Player  ana, const Judge & j,  Player & opponent,int d, SuperLeavesTrie superLeavesTrie);
	vector<Move> huristicMovesforEnd(Heuristic & heu, Board & board, Player & ana, Player & opponent, Bag b);
	Move simualteForPEG1(int id, Bag bag, Board board, Player ana, Heuristic heu, Judge judge, dictionary dec, Player p2);
	int simulateALLPeg1(Heuristic & heu, Board & board, bool game, Player ana, Player opponent, int sc, int cnt, Bag bag);
	//Move simualteForPEG2(int id, Bag bag, Board board, Player ana, Heuristic heu, Judge judge, dictionary dec, Player p2);

	/*int simFinal2(Heuristic & heu,  Board & board, bool game, Player ana, Player opponent, Bag & bag, int score,int cnt);
	int simulateALL(Heuristic & heu, Board & board, bool game, Player ana, Player opponent, int sc, int cnt, Bag bag);
	Move huristicMovesforEnd(Heuristic & heu, Board & board, Player & ana, Player & opponent, Bag b);
	Move simualteForPEG1(int id, Bag bag, Board board, Player p1, Heuristic heu, Judge j, dictionary dec, Player p2);*/



};
