//
// Created by riham on 24/10/18.
//
#include<iostream>
#include<cmath>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include <sstream>
using namespace std;
#include "Player.h"
Player::Player(int playerId) :
		playerId(playerId) {
	//if (playerId == 0)
	memset(myTies, 0, sizeof myTies);
	/*else
		for (int i = 0; i < 27; ++i)
			myTies[i] = 100;*/

}
Player::Player() {
	playerId = 0;
	memset(myTies, 0, sizeof myTies);
}
Player& Player::operator=(const Player & myObj) {
	playerId = myObj.playerId;
	score = myObj.score;
	totalTies = myObj.totalTies;
	memcpy(myTies, myObj.myTies, sizeof(myTies));
	return *this;
}
void Player::addValue(int v, int tie) {

	myTies[tie] = v;
}
int Player::getValue(int tie) const {

	return myTies[tie];
}
int Player::getPlayerID()  {
	return playerId;
}
bool Player::addTie(int tie) {
	if (totalTies >= PLAYER_TIES_SIZE || tie < 0 || tie > 26)
		return false;
	myTies[tie]++;
	totalTies++;
	return true;
}

bool Player::playTie(int tie) {

	if (tie < 0 || tie > 26 || myTies[tie] <= 0)
		return false; // the player doesn't have any ties
	myTies[tie]--;
	totalTies--;
	return true;
}

int Player::getTotalTies() {
	return totalTies;
}

int Player::getScore() {
	return score;
}

void Player::addScore(int scr) {
	score += scr;
}

void Player::putScore(int newScr) {
	score = newScr;
}

int Player::getTie(int pos) {
	if (pos < 0 || pos > 26)
		return -1;
	return myTies[pos];

}
void  Player::setTies(int t) {
	totalTies = t;


}

string Player::getTieStr() {
	string s = "";
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < myTies[i]; ++j)
			s += ('A' + i);

	if (myTies[26])
		s += 'e';
	return s;
}

ostream& operator<<(ostream& os, Player const& myObj) {
	os << "\n Player: " << myObj.playerId << "\t total number of ties: "
	   << myObj.totalTies << "\t Score"<< myObj.score << "\t ties: ";
	for (int i = 0; i < 26; i++) {
		if (myObj.myTies[i] != 0) {
			os << "( char=" << char(i + 'A') << ", count=" << myObj.myTies[i]
			   << " ) ";
		}
	}
	for (int i = 0; i < myObj.myTies[26]; i++) {
		os << "( char=" << 'e' << ", count=" << myObj.myTies[i]
			<< " ) ";
	}
	os << endl;
	return os;
}