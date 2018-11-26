//
// Created by riham on 24/10/18.
//

#include "Player.h"

Player::Player(int playerId) :
		playerId(playerId) {
	memset(myTies, 0, sizeof myTies);
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
		return false; // the player doesn't have any ties yet
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

ostream& operator<<(ostream& os, Player const& myObj) {
	os << "\nPlayer: " << myObj.playerId << "\ttotal number of ties: "
			<< myObj.totalTies << "\t ties: ";
	for (int i = 0; i < 27; i++) {
		if (myObj.myTies[i] != 0) {
			os << "( char=" << char(i + 'A') << ", count=" << myObj.myTies[i]
					<< " ) ";
		}
	}
	os << endl;
	return os;
}
