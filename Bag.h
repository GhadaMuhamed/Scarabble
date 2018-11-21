#ifndef SCRABBLE_BAG_H
#define SCRABBLE_BAG_H
#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include <sstream>

using namespace std;
// bag want acess value of id func get
class Bag {
	int bag[27] = { 9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6,
			4, 2, 2, 1, 2, 1, 2 };
	int bagSize = 100;
	int scores[27] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1,
			1, 1, 4, 4, 8, 4, 10, 0 };

public:
	// returns the length of the bag
	int bagLen();
	// it removes a tie from the bag and returns its score
	int removeTie(int index);
	// get Tie count
	int addTie(int index);
	int getTieCount(int index);
	// get Tie score
	int getTieScore(int index);
	// adding a tie to the bag in case of exchange
	bool exchangeTie(int src, int dst);
	// overriding the cout operator
	friend ostream& operator<<(ostream& os, Bag const& myObj);
	// equal operator overloading
	Bag& operator=(Bag const& myObj);
};
#endif //SCRABBLE_TIE_H
