//
// Created by riham on 24/10/18.
//

#ifndef SCRABBLE_PLAYER_H
#define SCRABBLE_PLAYER_H

#include<bits/stdc++.h>

using namespace std;

static const int PLAYER_TIES_SIZE = 7;

// want to acess totalTies for user func get
// what mean player id ?!! and value of it?!
class Player {
	int myTies[27];
	int totalTies = 0;
	int playerId;
	int score = 0;
public:
	Player(int playerId);
	Player();

	bool addTie(int tie);
	int getTotalTies();
	bool playTie(int tie);
	int getScore();
	void addScore(int scr);
	void putScore(int newScr);
	int getTie(int pos);
	string getTieStr();
	friend ostream& operator<<(ostream& os, Player const& myObj);
};

#endif //SCRABBLE_PLAYER_H
