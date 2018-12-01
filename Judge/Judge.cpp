//
// Created by riham on 26/10/18.
//

#include "Judge.h"
#include "../Bag/Bag.h"
Judge::Judge(int rem1, int rem2) {
	remTimePlayer=rem1;
	remTimeGame=rem2;

}

int Judge::applyMove(const Move &move, Board &board, Player &player, Bag &bag) {
	int score = 0, x = move.x, y = move.y;
	string word = move.playedWord;
	if (move.switchMove || word.size() == 0)
		return 0;
	int wordMultiplier = 1;
	if (move.direction == RIGHT) {
		// right
		int cnt = 0;
		while (cnt < word.size()) {
			// if it's successfully put then it was empty place, so remove it from the player
			int tie = int(word[cnt] - 'A');
			if (board.putTieMove(x, y, tie)) {
				player.playTie(tie);
			}
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			y++, cnt++;
		}
	} else if (move.direction == DOWN) {
		// up
		int cnt = 0;
		while (cnt < word.size()) {
			int tie = int(word[cnt] - 'A');
			if (board.putTieMove(x, y, tie)) {
				player.playTie(tie);
			}
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			x++, cnt++;
		}

	}

	return score * wordMultiplier;
}
int Judge::applyMoveMin(const Move &move, Board &board, Bag &bag) {
	int score = 0, x = move.x, y = move.y;
	string word = move.playedWord;
	if (move.switchMove || (int) word.size() == 0)
		return 0;
	int wordMultiplier = 1;
	if (move.direction == RIGHT) {
		// right
		int cnt = 0;
		while (cnt < word.size()) {
			// if it's successfully put then it was empty place, so remove it from the player
			int tie = int(word[cnt] - 'A');
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			y++, cnt++;
		}
	} else if (move.direction == DOWN) {
		// up
		int cnt = 0;
		while (cnt < word.size()) {
			int tie = int(word[cnt] - 'A');
			score += board.getMultiplierLetter(x, y) * bag.getTieScore(tie);
			wordMultiplier *= board.getMultiplierWord(x, y);
			x++, cnt++;
		}

	}

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
