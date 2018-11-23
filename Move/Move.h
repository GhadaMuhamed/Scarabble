#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<string>
#include <sstream>
using namespace std;
struct Move {
	string word;
	int x, y;
	bool direction;
	bool switchMove;
	vector<char> tiles;
	Move();
};
