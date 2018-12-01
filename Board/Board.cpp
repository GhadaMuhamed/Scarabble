//
// Created by riham on 24/10/18.
//

#include "Board.h"

Board::Board() {
	// init multiplier letter as 1
	for (auto& i : multiplier_letter)
		for (auto& j : i)
			j = 1;

	for (auto& i : multiplier_word)
		for (auto& j : i)
			j = 1;

	for (auto &i : board)
		for (auto &j : i)
			j = -1;

}

Board::Board(int b[][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j) {
			board[i][j] = b[i][j];
		}
}

void Board::initBoard() {
//    update board with 3xL
	for (auto &it : _3xL)
		multiplier_letter[it.first - 1][it.second - 1] = 3;

//    update board with 2xL
	for (auto &it : _2xL)
		multiplier_letter[it.first - 1][it.second - 1] = 2;

////////////////////////////////////////////
//    update board with 3xW
//    it triples the score of the current word
	for (auto &it : _3xW)
		multiplier_word[it.first - 1][it.second - 1] = 3;

//    update board with 2xW
//    it doubles the score of the current word
	for (auto it : _2xW)
		multiplier_word[it.first - 1][it.second - 1] = 2;

}

ostream& operator<<(ostream& os, Board const& myObj) {
	for (auto &i : myObj.board) {
		for (int j : i) {
			os << char(j + 'A') << " ";
		}
		os << endl;
	}
	return os;
}
int Board::getBoardValue(int posX, int posY) {
	return board[posX][posY];
}

bool Board::putFirstTie(int tie) {
	if (tie < 0 || tie > 26 || board[starPos][starPos] != -1)
		return false;
	board[starPos][starPos] = tie;
	ties_count++;
	return true;
}

bool Board::putTie(int posX, int posY, int tie) {
	if (tie < 0 || tie > 26 || posX < 0 || posX >= 15 || posY < 0 || posY >= 15
			|| board[posX][posY] != -1 || !isValidMove(posX, posY, tie))
		return false;
	board[posX][posY] = tie;
	ties_count++;
	return true;
}

bool Board::putTieMove(int posX, int posY, int tie) {
	if (tie < 0 || tie > 26 || board[posX][posY] != -1)
		return false;
	board[posX][posY] = tie;
	ties_count++;
	return true;
}

bool Board::isValidMove(int posX, int posY, int tie) {
	board[posX][posY] = tie;
	string horizontalWord = getHorizontalWord(posX, posY), verticalWord =
			getVerticalWord(posX, posY);
	cout << endl << horizontalWord << " " << verticalWord << endl;
	// call the dictionary module to make sure that horizontal and vertical words are correct
	// and make sure that the current tie is appended to at least one another tie
	if ((horizontalWord.size() > 1 || verticalWord.size() > 1)
			&& isValidWords(horizontalWord, verticalWord))
		return true;
	board[posX][posY] = -1;
	return false;
}

string Board::getHorizontalWord(int posX, int posY) {
	string horizontalWord = "";
	int r = posX, c = posY;
	// if it's a blank tie it should be handled to be replaced by a suitable char
	while (c >= 0 && board[r][c] != -1) {
		horizontalWord = char(board[r][c] + 'A') + horizontalWord;
		c--;
	}
	c = posY + 1;
	while (c < BOARD_SIZE && board[r][c] != -1) {
		horizontalWord += char(board[r][c] + 'A');
		c++;
	}
	return horizontalWord;
}

string Board::getVerticalWord(int posX, int posY) {
	string verticalWord = "";
	int r = posX, c = posY;
	while (r >= 0 && board[r][c] != -1) {
		verticalWord = char(board[r][c] + 'A') + verticalWord;
		r--;
	}
	r = posX + 1;
	while (r < BOARD_SIZE && board[r][c] != -1) {
		verticalWord += char(board[r][c] + 'A');
		r++;
	}
	return verticalWord;
}

bool Board::isValidWords(string& horWord, string& verWord) {
	// it calls the dictionary to make sure that these words exist in it
	return true;
}

int Board::getMultiplierLetter(int posX, int posY) {
	return multiplier_letter[posX][posY];
}

int Board::getMultiplierWord(int posX, int posY) {
	return multiplier_word[posX][posY];
}

int Board::tiesCount() {
	return ties_count;
}
