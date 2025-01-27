//
// Created by riham on 24/10/18.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include<fstream>
#include <string>
#include <sstream>
#include <cstring>
#include<map>
#include<queue>
#include<math.h>
#include<algorithm>

#include "Board.h"
using namespace std;
/*
 * Board empty position => -1
 * Board characters => 0 ~ 25
 * Board blank characters => 100 ~ 125
 * */


void Board::initBoard() {
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

Board::Board() {
	initBoard();
}
Board::Board(uint8_t b[][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j) {
			board[i][j] = b[i][j];
		}
}

ostream& operator<<(ostream& os, Board const& myObj) {
	for (auto &i : myObj.board) {
		for (int j : i) {
			if (j >= 100 && j <= 125) {
				os << (j == -1 ? 0 : myObj.scores[j]) << char(j - 100 + 'a') << " ";
			} else 
				os << (j == -1? 0 : myObj.scores[j]) << char(j + 'A') << " ";
		}
		os << endl;
	}
	return os;
}
int Board::getBoardValue(int posX, int posY) {
	// if this position on the board isn't occupied the it's -1 otherwise it's already occupied.
	return board[posX][posY];
}
void Board::getBoard(uint8_t b[][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			b[i][j] = (uint8_t) board[i][j];
}

bool Board::putFirstTie(int tie) {
	if (!((tie >= 0 && tie < 27) || (tie >= 100 && tie < 126)) || board[starPos][starPos] != -1)
		return false;
	board[starPos][starPos] = tie;
	ties_count++;
	return true;
}

bool Board::isValidPos(int tie, int posX, int posY) {
	return ((tie >= 0 && tie < 27) || (tie >= 100 && tie < 126)) && posX >= 0 && posX < 15 && posY >= 0
			&& posY < 15;
}

bool Board::putTie(int posX, int posY, int tie) {
	// checks that this move is valid before applying it
	if (!isValidPos(tie, posX, posY) || board[posX][posY] != -1
			|| !isValidMove(posX, posY, tie))
		return false;
	applyMove(posX, posY, tie);
	return true;
}

void Board::applyMove(int posX, int posY, int tie) {
	// it puts the tie without checking whether it's a valid move or not
	board[posX][posY] = tie;
	ties_count++;
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

// assumes that this position is occupied
// if the board value between 100~125 then the char is small
string Board::getHorizontalWord(int posX, int posY) {
	string horizontalWord = "";
	int r = posX, c = posY;
	// if it's a blank tie it should be handled to be replaced by a suitable char
	while (c >= 0 && board[r][c] != -1) {
		if (board[r][c] >= 100 && board[r][c] < 126)
			horizontalWord = char(board[r][c] - 100 + 'a') + horizontalWord;
		else horizontalWord = char(board[r][c] + 'A') + horizontalWord;
		c--;
	}
	c = posY + 1;
	while (c < BOARD_SIZE && board[r][c] != -1) {
		if (board[r][c] >= 100 && board[r][c] < 126)
			horizontalWord += char(board[r][c] - 100 + 'a');
		else horizontalWord += char(board[r][c] + 'A');
		c++;
	}
	return horizontalWord;
}

// assumes that this position is occupied
// if the board value between 100~125 then the char is small
string Board::getVerticalWord(int posX, int posY) {
	string verticalWord = "";
	int r = posX, c = posY;
	while (r >= 0 && board[r][c] != -1) {
		if (board[r][c] >= 100 && board[r][c] < 126)
			verticalWord = char(board[r][c] - 100 + 'a') + verticalWord;
		else verticalWord = char(board[r][c] + 'A') + verticalWord;
		r--;
	}
	r = posX + 1;
	while (r < BOARD_SIZE && board[r][c] != -1) {
		if (board[r][c] >= 100 && board[r][c] < 126)
			verticalWord += char(board[r][c] - 100 + 'a');
		else verticalWord += char(board[r][c] + 'A');
		r++;
	}
	return verticalWord;
}

string Board::getHorizontalWordWithTie(int posX, int posY, int tie) {
	swap(board[posX][posY], tie);
	string horWord = getHorizontalWord(posX, posY);
	swap(board[posX][posY], tie);
	return horWord;
}

string Board::getVerticalWordWithTie(int posX, int posY, int tie) {
	swap(board[posX][posY], tie);
	string verWord = getVerticalWord(posX, posY);
	swap(board[posX][posY], tie);
	return verWord;
}

int Board::getHorizontalWordScore(int posX, int posY) {
	int horizontalWordScore = 0, wordMultiplier = 1;

	int r = posX, c = posY - 1;
	while (c >= 0 && board[r][c] != -1) {
		if (board[r][c] >= 0 && board[r][c] < 26) { // if it wasn't blank then append it's score
			horizontalWordScore += scores[ board[r][c] ] * multiplier_letter[r][c];
		}
		wordMultiplier *= multiplier_word[r][c];
		c--;
	}
	c = posY + 1;
	while (c < BOARD_SIZE && board[r][c] != -1) {
		if (board[r][c] >= 0 && board[r][c] < 26) { // if it wasn't blank then append it's score
			horizontalWordScore += scores[ board[r][c] ] * multiplier_letter[r][c];
		}
		wordMultiplier *= multiplier_word[r][c];
		c++;
	}
	return horizontalWordScore * wordMultiplier;
}

int Board::getVerticalWordScore(int posX, int posY) {
	int verticalWordScore = 0, wordMultiplier = 1;

	int r = posX - 1, c = posY;
	while (r >= 0 && board[r][c] != -1) {
		if (board[r][c] >= 0 && board[r][c] < 26) { // if it wasn't blank then append it's score
			verticalWordScore += scores[ board[r][c] ] * multiplier_letter[r][c];
		}
		wordMultiplier *= multiplier_word[r][c];
		r--;
	}
	r = posX + 1;
	while (r < BOARD_SIZE && board[r][c] != -1) {
		if (board[r][c] >= 0 && board[r][c] < 26) { // if it wasn't blank then append it's score
			verticalWordScore += scores[ board[r][c] ] * multiplier_letter[r][c];
		}
		wordMultiplier *= multiplier_word[r][c];
		r++;
	}
	return verticalWordScore * wordMultiplier;
}

bool Board::isValidWords(string& horWord, string& verWord) {
	// it calls the dictionary to make sure that these words exist in it
	return true;
}

int Board::getMultiplierLetter(int posX, int posY) {
	return multiplier_letter[posX][posY];
}

bool Board::clearMultiplierLetter(int posX, int posY) {
	if (posX < 0 || posY >= 15) return false;
	multiplier_letter[posX][posY] = 0;
	return true;
}

int Board::getMultiplierWord(int posX, int posY) {
	return multiplier_word[posX][posY];
}

Board& Board::operator=(Board const& myObj) {
	ties_count = myObj.ties_count;
	memcpy(board, myObj.board, sizeof(board));
	return *this;
}

int Board::tiesCount() {
	return ties_count;
}
string Board::getRow(int i) {
	string row = "";
	for (int j = 0; j < 15;++j) {
		row += (board[i][j] != -1)?  char(board[i][j] + 'A'): ' ';
	}
	return row;
}
string Board::getCoulmn(int i) {

	string col = "";
	for (auto &j : board) {
		col += (j[i] != -1) ? char(j[i] + 'A') : ' ';
	}
	return col;
}

