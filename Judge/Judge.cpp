//
// Created by riham on 26/10/18.
//

#include "Judge.h"
#include "../Bag/Bag.h"
Judge::Judge() {


}


int Judge::applyMove(const Move &move, Board &board, Player &player, Bag &bag) {
    // it applies the move and do changes on the variables
	int score = 0, r = move.x, c = move.y;
	int playerTiesCnt = 0, asideScores = 0, wordMultiplier = 1;
	string word = move.playedWord;
	if (move.switchMove || word.empty())
		return 0;
    for (auto chr: word) {
        // if it's successfully put then it was empty place, so remove it from the player
        int tie = int(chr - 'A');
        if (board.getBoardValue(r, c) == -1) {
            // then it's empty, so the player is playing this
            player.playTie(tie);
            board.applyMove(r, c, tie);
            // getting the vertical word from this position
            asideScores += (move.direction == RIGHT ? board.getVerticalWordScore(r, c) :
                                                         board.getHorizontalWordScore(r, c));
            playerTiesCnt++;
        }
        score += board.getMultiplierLetter(r, c) * bag.getTieScore(tie);
        wordMultiplier *= board.getMultiplierWord(r, c);
        move.direction == RIGHT? c++ : r++;
    }
	// if the player played all of its rock then the score increases by 50
	if (playerTiesCnt == 7) score += 50;

	return score * wordMultiplier + asideScores;
}

// @Ghada
// QUESTION: Am I supposed to change apply move no change to this configurations? *small letters means blank*
// I've already changed it...
int Judge::applyMoveNoChange(const Move &move, Board &board, Bag &bag) {
    // it applies the move without doing any changes on the variables
	int score = 0, r = move.x, c = move.y, playerTiesCnt = 0, asideScores = 0;
	string word = move.playedWord;
	int wordMultiplier = 1;

	if (move.switchMove || word.empty()) {
		return 0;
	}

    for (auto chr: word) {
        int tie = -1;
        bool zeroLetter = false;
        if (chr >= 'a' && chr <= 'z') {
            // small letter
            zeroLetter = true;
            tie = int(chr - 'a');
        } else tie = int(chr - 'A');

        if (board.getBoardValue(r, c) == -1) {
            // then it's empty, so the player is playing this
            // getting the vertical word from this position
            asideScores += (move.direction == RIGHT ? board.getVerticalWordScore(r, c) :
                                                        board.getHorizontalWordScore(r, c));
            playerTiesCnt++;
        }
        score += zeroLetter? 0 : (board.getMultiplierLetter(r, c) * bag.getTieScore(tie)); // if it's blank then don't calculate its score
        wordMultiplier *= board.getMultiplierWord(r, c);
        move.direction == RIGHT ? c++ : r++;
    }
	// if the player played all of its rock then the score increases by 50
	if (playerTiesCnt == 7) score += 50;
	return score * wordMultiplier + asideScores;
}

// @Ghada
// for dictionary -> I'm changing on the board
// the small letters on the word means blank so I'm setting the multiplier letter on that pos by 0 [for score]
// if apply move also has the same configurations *small letters means blank* then I'll merge the two funcs
int Judge::applyMoveDic(const Move &move, Board &board, Player player, Bag &bag) {
    // it applies the move without doing any changes on the variables
    int score = 0, r = move.x, c = move.y, playerTiesCnt = 0, asideScores = 0;
    string word = move.playedWord;
    int wordMultiplier = 1;

    if (move.switchMove || word.empty()) {
        return 0;
    }

    for (auto chr: word) {
        int tie = -1;
        if (chr >= 'a' && chr <= 'z') {
            // small letter
            board.clearMultiplierLetter(r, c);
            tie = int(chr - 'a');
        }
        else tie = int(chr - 'A');
        if (board.getBoardValue(r, c) == -1) {
            // then it's empty, so the player is playing this
            player.playTie(tie);
            board.applyMove(r, c, tie);
            // getting the vertical word from this position
            asideScores += (move.direction == RIGHT ? board.getVerticalWordScore(r, c) :
                            board.getHorizontalWordScore(r, c));
            playerTiesCnt++;
        }
        score += board.getMultiplierLetter(r, c) * bag.getTieScore(tie);
        wordMultiplier *= board.getMultiplierWord(r, c);
        move.direction == RIGHT ? c++ : r++;
    }
    // if the player played all of its rock then the score increases by 50
    if (playerTiesCnt == 7) score += 50;
    return score * wordMultiplier + asideScores;
}

// TODO: Add communication configuration *don't know which*

bool Judge::isClosed(Board &board) {
	// count of the ties in board is 100 the it's closed
	return board.tiesCount() >= 100;
}

void Judge::nCr() {
	for (int i = 0; i < 101; i++)
		pascal[i][0] = 1, pascal[i][i] = 1;
	for (int i = 2; i < 101; i++)
		for (int j = 1; j < 101; j++)
			pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];

}
