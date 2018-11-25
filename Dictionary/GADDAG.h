#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>


struct node
{
	char charcter;
	node** pointers;
	node(char c)
	{
		charcter = c;
		pointers = new node*[28];
		for (int i = 0; i < 28; ++i)
			pointers[i] = nullptr;
	}
};

class GADDAG
{
public:
	node* root;
	std::vector<std::pair<std::pair<std::string, std::string>,int>> returnVector;

public:
	GADDAG();
	void insertWord(std::string &word);
	void insertChar(node* myroot, std::string &word, int start);
	void search(std::string word,std::string board,int start,int indicator);
	void search(std::string word);
	void select(node *myroot,std::string word,std::string board, int start,int &golbalStart,std::string newWord,int indicator,int first,bool check);
	void select(node *myroot, std::string word,std::string newWord,bool check=false);
	bool check(node *myroot, std::string word, int c = 0);
	void deleteNodes(node* root);
	void check(node *myroot);

	~GADDAG();
};

