#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "GADDAG.h"
#include "../Move/Move.h"


struct Word {
	std::string word;
	std::string rack;
	std::pair<int, int> location; //(y,x) ==(row,column)
	int direction;  //   0= horizontal  1=vertical
};

class dictionary
{
	GADDAG data;
	std::vector<Move>returnVec;
public:
	

	dictionary();
	dictionary(std::string filename);

	void search(std::string board,std::string word);
	void search(std::string board, std::string word,int index);
	bool check(std::string word);

	void selectAll(std::string word);
	std::vector<std::string>cast(int board[15][15]);
	void test();
	std::string convert(std::string word);
	std::string reverse(std::string word);
	void execute(int board[15][15],std::string rack);

	~dictionary();
	
};

