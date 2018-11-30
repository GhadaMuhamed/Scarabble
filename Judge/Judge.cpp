//
// Created by riham on 26/10/18.
//

#include "Judge.h"
#include "../Bag/Bag.h"

int Judge::applyMove(const Move &move, Board &board, Player &player, Bag &bag) {
    // it applies the move and do changes on the variables
	int score = 0, x = move.x, y = move.y, playerTiesCnt = 0;
	string word = move.playedWord;
	if (move.switchMove || word.empty())
		return 0;
	int wordMultiplier = 1;
	if (move.direction == RIGHT) {
		// right
		int cnt = 0;
		while (cnt < word.size()) {
			// if it's successfully put then it was empty place, so remove it from the player
			int tie = int(word[cnt] - 'A');
			if (board.applyMove(x, y, tie)) {
				playerTiesCnt++;
				player.playTie(tie);
			}
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			y++, cnt++;
		}
	} else if (move.direction == UP) {
		// up
		int cnt = 0;
		while (cnt < word.size()) {
			int tie = int(word[cnt] - 'A');
			if (board.applyMove(x, y, tie)) {
				playerTiesCnt++;
				player.playTie(tie);
			}
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			x++, cnt++;
		}

	}
	// if the player played all of its rock then the score increases by 50
	if (playerTiesCnt == 7) score += 50;

	return score * wordMultiplier;
}
int Judge::applyMoveNoChange(const Move &move, Board &board, Bag &bag) {
    // it applies the move without doing any changes on the variables
	int score = 0, x = move.x, y = move.y, playerTiesCnt = 0;
	string word = move.playedWord;
	int wordMultiplier = 1;

	if (move.switchMove || word.empty()) {
		return 0;
	}

	if (move.direction == RIGHT) {
		// right
		int cnt = 0;
		while (cnt < word.size()) {
			int tie = int(word[cnt] - 'A');
			if (board.getBoardValue(x, y) == -1) {
				// then it's empty, so the player is playing this
				playerTiesCnt++;
			}
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			y++, cnt++;
		}
	} else if (move.direction == UP) {
		// up
		int cnt = 0;
		while (cnt < word.size()) {
			int tie = int(word[cnt] - 'A');
			if (board.getBoardValue(x, y) == -1) {
				// then it's empty, so the player is playing this
				playerTiesCnt++;
			}
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			x++, cnt++;
		}

	}
	// if the player played all of its rock then the score increases by 50
	if (playerTiesCnt == 7) score += 50;
	return score * wordMultiplier;
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
