/*
 * dictionary.h
 *
 *  Created on: Nov 25, 2018
 *      Author: ghada
 */

#ifndef DICTIONARY_DICTIONARY_H_
#define DICTIONARY_DICTIONARY_H_


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "GADDAG.h"
#include "../Move/Move.h"
#include "../Board/Board.h"

using namespace std;

struct Word {
	string word;
	string rack;
	pair<int, int> location; //(y,x) ==(row,column)
	int direction;  //   0= horizontal  1=vertical
};

class dictionary {
	GADDAG data;
	vector<Move> returnVec;
public:

	dictionary();
	dictionary(std::string filename);

	void search(std::string board, std::string word);
	void search(std::string board, std::string word, int index);
	bool check(std::string word);

	void selectAll(std::string word);
	vector<string> cast(int board[15][15]);
	void test();
	vector<Move> getVector();
	void execute(Board& b, string rack);

	~dictionary();

};




#endif /* DICTIONARY_DICTIONARY_H_ */
