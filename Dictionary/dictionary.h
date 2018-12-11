#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "GADDAG.h"
#include "../Move/Move.h"
#include"../Board/Board.h"
struct Word {
	std::string word;
	std::string rack;
	std::pair<int, int> location; //(y,x) ==(row,column)
	int direction;  //   0= horizontal  1=vertical
};

class dictionary {
	
	std::vector<Move> returnVec;
public:
	GADDAG data;
	dictionary();
	dictionary(std::string filename);
	void search(std::string board, std::string word,int vecSize);
	void search(std::string board, std::string word, int index,int vecSize);
	bool check(std::string word);
	vector<string> selectAll(std::string word);
	std::vector<std::string> cast(int board[15][15]);
	void test();
	vector<Move> getVector();
	std::string smallize(std::string word);
	std::string convert(std::string word, bool rack=false);
	std::string reverse(std::string word, bool rack=false);
	void execute(Board& board, std::string rack,int vecSize=-1);
	void checkOne(int index,int index2,string rack,vector<string> row, string col,int vecSize);
	int checkWord(int index, int index2, vector<string> row, string col);
	~dictionary();

};
