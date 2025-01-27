//
// Created by riham on 26/10/18.
//

#ifndef SCRABBLE_JUDGE_H
#define SCRABBLE_JUDGE_H

#include "../Dictionary/dictionary.h"
#include "../Bag/Bag.h"
#include "../Board/Board.h"
#include "../Player/Player.h"
#include "../Move/Move.h"

#define RIGHT   0
#define DOWN      1

class Judge {
public:
	Judge();
	long long pascal[101][101];
	int applyMove(const Move &move, Board &board, Player &player, Bag &bag);
    int applyMoveNoChange(const Move &move, Board &board, Bag &bag);
    bool isValidMove(Move move, Board& board, dictionary& dic);
    bool isClosed(Board &board);
	void nCr();
	pair<int, string> getFormedWord(const Move &move, Board &board, Bag &bag);
};

#endif //SCRABBLE_JUDGE_H
