#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

struct nodeG
{
	char charcter;
	nodeG** pointers;
	nodeG(char c)
	{
		charcter = c;
		pointers = new nodeG*[28];
		for (int i = 0; i < 28; ++i)
			pointers[i] = nullptr;
	}
};

class GADDAG
{	
public:
	nodeG* root;
	std::vector<std::pair<std::pair<std::string, std::string>,int>> returnVector;
	std::vector<std::string> y;
public:
	GADDAG();
	void insertWord(std::string &word);
	void insertChar(nodeG* myroot, std::string &word, int start);
	void select(nodeG *myroot, std::string word, std::string board, int start, int &golbalStart, std::string newWord, int indicator, int first, bool check,int vicSize);
	void select(nodeG *myroot, std::string word, std::string newWord, bool check = false,bool use=false);
	void search(std::string word,std::string board,int start,int indicator,int vecSize);
	void search(std::string word);
	
	bool check(nodeG *myroot, std::string word, int c = 0);
	void deletenodeGs(nodeG* root);
	void check(nodeG *myroot);
	~GADDAG();
};

