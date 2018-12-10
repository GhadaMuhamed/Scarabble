//
// Created by riham on 26/10/18.
//

#include "Judge.h"
#include "../Bag/Bag.h"
Judge::Judge(dictionary d): dic(d) {

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
        int blankMargin = 0;
        if (islower(chr)) {
            tie = int(chr - 'a');
            blankMargin = 100;
        }
        if (board.getBoardValue(r, c) == -1) {
            // then it's empty, so the player is playing this
            player.playTie(tie);

            board.applyMove(r, c, tie + blankMargin); // if it's lower case then put in the board from range 100~125
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

int Judge::applyMoveNoChange(const Move &move, Board &board, Bag &bag) {
    // it calculates the move's score without doing any changes on the game
	int score = 0, r = move.x, c = move.y, playerTiesCnt = 0, asideScores = 0;
	string word = move.playedWord;
	int wordMultiplier = 1;

	if (move.switchMove || word.empty()) {
		return 0;
	}

    for (auto chr: word) {
        int tie = -1;
        bool notZeroScore = true;
        if (chr >= 'a' && chr <= 'z') {
            // small letter
            notZeroScore = false;
            tie = int(chr - 'a');
        } else tie = int(chr - 'A');

        if (board.getBoardValue(r, c) == -1) {
            // then it's empty, so the player is playing this
            // getting the vertical word from this position
            asideScores += (move.direction == RIGHT ? board.getVerticalWordScore(r, c) :
                                                        board.getHorizontalWordScore(r, c));
            playerTiesCnt++;
        }
        score += notZeroScore * board.getMultiplierLetter(r, c) * bag.getTieScore(tie); // if it's blank then don't calculate its score
        wordMultiplier *= board.getMultiplierWord(r, c);
        move.direction == RIGHT ? c++ : r++;
    }
	// if the player played all of its rock then the score increases by 50
	if (playerTiesCnt == 7) score += 50;
	return score * wordMultiplier + asideScores;
}

bool Judge::isValidMove(Move move, Board board) {
    string playedWord = move.playedWord;
    if (move.switchMove || !move.tiles.empty()) // if it's exchange or pass then okay it's vaid
    {
        return true;
    }
    if (playedWord.empty()) return false;
    int r = move.x, c = move.y;
    string allWord = move.direction == RIGHT? board.getHorizontalWord(r, c) :
                                            board.getVerticalWord(r, c);

    if (allWord.empty() || !dic.check(allWord)) return false;

    for (auto chr: playedWord) {
        if (r >= 15 || c >= 15) return false; // out of boundary (I think impossible case?)

        int tie = int(chr - 'A');
        if (chr >= 'a' && chr <= 'z') {
            // small letter
            tie = int(chr - 'a') + 100;
        }

        if (board.getBoardValue(r, c) == -1) {
            string asideWord = (move.direction == RIGHT? board.getVerticalWordWithTie(r, c, tie) :
                                                    board.getHorizontalWordWithTie(r, c, tie));
            // check that this playedWord is contained on the dictionary
            if ( !dic.check(asideWord) ) return false; // this playedWord doesn't exist
        }
        move.direction == RIGHT? c++ : r++;
    }
    return true;
}

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
