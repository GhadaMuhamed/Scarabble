//
// Created by riham on 26/10/18.
//

#ifndef SCRABBLE_JUDGE_H
#define SCRABBLE_JUDGE_H


#include "../Bag/Bag.h"
#include "../Board/Board.h"
#include "../Player/Player.h"
#include "../Move/Move.h"

#define RIGHT   0
#define LEFT    1
#define UP      2
#define DOWN    3

class Judge {
public:
    long long pascal[101][101];
    int applyMove(const Move &move, Board &board, Player &player, Bag &bag);
    int applyMoveMin(const Move &move, Board &board, Bag &bag);
    bool isClosed(Board &board);
	void nCr();
};


#endif //SCRABBLE_JUDGE_H