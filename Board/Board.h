#pragma once
//
// Created by riham on 24/10/18.
//

#ifndef SCRABBLE_BOARD_H
#define SCRABBLE_BOARD_H

#include <bits/stdc++.h>
using namespace std;

static const int BOARD_SIZE = 15;
static const int _3xW_SIZE = 7;
static const int _2xW_SIZE = 12;
static const int _3xL_SIZE = 12;
static const int _2xL_SIZE = 24;
// func close or variable mean all board off
class Board {
	int scores[27] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1,
			1, 1, 4, 4, 8, 4, 10, 0 };

	int multiplier_letter[BOARD_SIZE][BOARD_SIZE];
	int multiplier_word[BOARD_SIZE][BOARD_SIZE];
	int board[BOARD_SIZE][BOARD_SIZE];
	int starPos = 7;
	int ties_count = 0;
	pair<int, int> _3xW[_3xW_SIZE] = { { 1, 1 }, { 8, 1 }, { 15, 1 }, { 1, 8 },
			{ 1, 15 }, { 8, 15 }, { 15, 15 } };
	pair<int, int> _2xW[_2xW_SIZE] = { { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, {
			14, 2 }, { 13, 3 }, { 12, 4 }, { 11, 5 }, { 11, 11 }, { 12, 12 }, {
			13, 13 }, { 14, 14 } };
	pair<int, int> _3xL[_3xL_SIZE] = { { 6, 2 }, { 10, 2 }, { 2, 6 }, { 6, 6 },
			{ 10, 6 }, { 14, 6 }, { 2, 10 }, { 6, 10 }, { 10, 10 }, { 14, 10 },
			{ 6, 14 }, { 10, 14 } };
	pair<int, int> _2xL[_2xL_SIZE] = { { 4, 1 }, { 12, 1 }, { 7, 3 }, { 9, 3 },
			{ 1, 4 }, { 8, 4 }, { 15, 4 }, { 3, 7 }, { 7, 7 }, { 9, 7 },
			{ 13, 7 }, { 4, 8 }, { 12, 8 }, { 3, 9 }, { 7, 9 }, { 9, 9 }, { 13,
					9 }, { 1, 12 }, { 8, 12 }, { 15, 12 }, { 7, 13 }, { 9, 13 },
			{ 4, 15 }, { 12, 15 } };
public:
	Board();
	Board(uint8_t b[][BOARD_SIZE]);
	void initBoard();
	friend ostream& operator<<(ostream& os, Board const& myObj);
	bool putFirstTie(int tie);
	bool putTie(int posX, int posY, int tie);
	void applyMove(int posX, int posY, int tie);
	bool isValidMove(int posX, int posY, int tie);
	int getBoardValue(int posX, int posY);
	string getHorizontalWord(int posX, int posY);
	string getVerticalWord(int posX, int posY);
	int getHorizontalWordScore(int posX, int posY);
	int getVerticalWordScore(int posX, int posY);
	bool isValidPos(int tie, int posX, int posY);
	bool isValidWords(string& horWord, string& verWord);
	int getMultiplierLetter(int posX, int posY);
	bool clearMultiplierLetter(int posX, int posY);
	int getMultiplierWord(int posX, int posY);
	int tiesCount();
	void getBoard(uint8_t b[][BOARD_SIZE]);
	Board& operator=(Board const& myObj);
};

#endif //SCRABBLE_BOARD_H
