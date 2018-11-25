/*
 * Heuristic.cpp
 *
 *  Created on: Nov 25, 2018
 *      Author: ghada
 */
#include "Heuristic.h"
#include<bits/stdc++.h>
using namespace std;
Heuristic::Heuristic(Board b, dictionary d, Bag bg, Judge j) {
	// TODO Auto-generated constructor stub
	board = b;
	dec = d;
	bag = bg;
	J = j;
}

Heuristic::~Heuristic() {
	// TODO Auto-generated destructor stub
}
void Heuristic::setBoard(Board b) {
	board = b;
}
void Heuristic::setBag(Bag b) {
	bag = b;
}
bool Heuristic::filterPossibles(string s, int cur[]) {
	int freq[26];
	memset(freq, 0, sizeof(freq));
	for (int j = 0; j < s.size(); ++j)
		freq[s[j] - st]++;
	for (int j = 0; j < 26; ++j)
		if (((freq[j] < cur[j] || freq[j] > cur[j] + bag.getTieScore(j))))
			return false;

	return true;
}
///implement for omnia
// btgeeb kol el strings eli mn 7 chars eli law et7tet fl board t3ml bingo
vector<pair<string, int>> Heuristic::getPossibleBingo(string str, int cur[]) {

	dec.execute(board, str);
	vector<Move> v = dec.getVector();
	vector<pair<string, int> > ret;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].word.size())
			continue;
		if (!filterPossibles(v[i].playedWord, cur))
			continue;
		//////////////////////////////////////////////////////
		// h7sb el score
		int score = 0;
		pair<string, int> p = { v[i].playedWord, score };
		ret.push_back(p);
	}
	return ret;

}

double Heuristic::calcProbability(int freq[], int score, int cur[]) {

	double letterP = 1;
	int cnt = 0;
	for (int i = 0; i < 26; ++i) {
		if (cur[i] >= freq[i])
			continue;
		// cur[i] hya el 7rof eli m3aya
		freq[i] -= cur[i];
		cnt += freq[i];
		letterP *= J.pascal[bag.getTieCount(i)][freq[i]];
	}
	letterP /= (J.pascal[bag.bagLen()][cnt] * 1.0);
// multiply by 2.5 if the score isn't calculated for the board
	return letterP * (50 + score);
}
// mmkn ab2a a3mlni class w a5ali m3aya nos5a ml bag object a7sn
double Heuristic::expectedBingoMe(string s, Player &player) {
	if (s.size() == 7)
		return 0.0;
	int freq[27], cur[27];
	memset(freq, 0, sizeof(freq));
	memset(cur, 0, sizeof(cur));
	for (int i = 0; i < 26; ++i)
		cur[i] = player.gitTie(i);
	string curStr = "";
	for (int i = 0; i < s.size(); ++i)
		cur[s[i] - st]--;
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < cur[i]; ++j)
			curStr += char(i + st);
	if (cur[26])
		curStr += 'e';
	vector<pair<string, int>> possible = getPossibleBingo(curStr, cur);
//possible = filterPossibles(possible, cur);
	double p = 0;
	for (int i = 0; i < possible.size(); ++i) {
		memset(freq, 0, sizeof(freq));
		for (int j = 0; j < possible[i].first.size(); ++j)
			freq[possible[i].first[j] - st]++;

		// calculate the expected number of the score to make this word
		p += calcProbability(freq, possible[i].second, cur);
	}
	return p * 0.8; // multiply  p * 0.8 assuming prob of bingo in the next play will decrease by 0.2
}
int Heuristic::expectedBingoOpponent() {
	vector<pair<string, int>> possible; //= getPossibleBingo();
//////--------------- not so sure
	int mx = -1;
	for (int i = 0; i < possible.size(); ++i) {
		mx = max(mx, possible[i].second);
	}
	return -mx;
// eb3ty el mx
//////////////// mfrod ab3t el exScore
}

double Heuristic::RackLeaveScore(string C) {

	double score = 0.0;

//The weights for the first occurence of a letter
// * means blank
	map<char, double> L1 { { 'a', 1.0 }, { 'b', -3.5 }, { 'c', -0.5 }, { 'd',
			0.0 }, { 'e', 4.0 }, { 'f', -2.0 }, { 'g', -2.0 }, { 'h', 0.5 }, {
			'i', -0.5 }, { 'j', -3.0 }, { 'k', -2.5 }, { 'l', -1.0 }, { 'm',
			-1.0 }, { 'n', 0.5 }, { 'o', -1.5 }, { 'p', -1.5 }, { 'q', -11.5 },
			{ 'r', 1.5 }, { 's', 7.5 }, { 't', 0.0 }, { 'u', -3.0 },
			{ 'v', -5.5 }, { 'w', -4.0 }, { 'x', 3.5 }, { 'y', -2.0 }, { 'z',
					2.0 }, { '*', 24.5 } // '*' means blank
	};

//Duplicate weights
	map<char, double> L2 { { 'a', -3.0 }, { 'b', -3.0 }, { 'c', -3.5 }, { 'd',
			-2.5 }, { 'e', -2.5 }, { 'f', -2.0 }, { 'g', -2.5 }, { 'h', -3.5 },
			{ 'i', -4.0 }, { 'j', 0.0 }, { 'k', 0 }, { 'l', -2.0 },
			{ 'm', -2.0 }, { 'n', -2.5 }, { 'o', -3.5 }, { 'p', -2.5 },
			{ 'q', 0 }, { 'r', -3.5 }, { 's', -4.0 }, { 't', -2.5 },
			{ 'u', -3.0 }, { 'v', -3.5 }, { 'w', -4.5 }, { 'x', 0 },
			{ 'y', -4.5 }, { 'z', 0 }, { '*', 15.0 } };
	/*j,k,q,x,z mknsh lehm rkm w 5lthm bzero,mmkn ab2a ashelhm mn lmap dh
	 w a5od rkmhm mn fo2 k2nhm msh duplicate!
	 */

	char x;
	map<char, double> m;  // The accumulative weight for each letter in the rack
	int v = 0, c = 0; //the number of vowels and constants

	for (int i = 0; i < C.length(); i++) {
		x = C[i];
		if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u')
			v++;
		else
			c++;

		if (m.count(x) == 0)
			m[x] = L1[x];
		else
			m[x] += L2[x];

		score += m[x];
	}
//------------------------------------------------------------------
//Vowel--Consonant Mix weights
	map<string, double> VC { { "00", 0 }, { "01", 0 }, { "02", -1 },
			{ "03", -2 }, { "04", -3 }, { "05", -4 }, { "06", -5 },
			{ "10", -1 }, { "11", 1 }, { "12", 1 }, { "13", 0 }, { "14", -1 }, {
					"15", -2 }, { "20", -2 }, { "21", 0 }, { "22", 2 }, { "23",
					2 }, { "24", 1 }, { "30", -3 }, { "31", -1 }, { "32", 1 }, {
					"33", 3 }, { "40", -4 }, { "41", -2 }, { "42", 0 }, { "50",
					-5 }, { "51", -3 }, { "60", -6 } };

	string r_vc;
	r_vc = v + '0';
	r_vc += (c + '0');

	score += VC[r_vc];

	return score;
}

//----------------------->will be modified later depending on what will bs sent
double Heuristic::DefensiveStrategy(Move move) {
	double perm = 0.0;
	vector<int> newWord;
	newWord.push_back(move.direction);
	if (newWord[0] == 0) {
		newWord.push_back(move.y);
		for (int i = 0; i < move.word.size(); ++i)
			newWord.push_back(move.x + i);
	} else {
		newWord.push_back(move.x);
		for (int i = 0; i < move.word.size(); ++i)
			newWord.push_back(move.y + i);
	}

	int Wlen = newWord.size();
	/*
	 newWord{0 if horizontal 1 if vertical,index 1 is the row # in case of horizantal
	 and column # in case of vertical word,
	 rest of number are column indexes in case of horizontal
	 and row indexes in case of vertical
	 */
	int d_factor = 1;
	double n = 1;
//horizontal word
	if (newWord[0] == 0) {
		//search horizontally--left of the word
		for (int i = newWord[2] - 1; i >= (newWord[2] - 3) && i >= 0; i--) {
			if (board.getBoardValue(newWord[1], i) == 0) //no letter in this box
					{
				if (board.getMultiplierLetter(newWord[1], i) == 2)
					perm += d_factor * 0.4;
				else if (board.getMultiplierLetter(newWord[1], i) == 3)
					perm += d_factor * 0.8;
				else if (board.getMultiplierWord(newWord[1], i) == 2)
					perm += d_factor * 1.2;
				else if (board.getMultiplierWord(newWord[1], i) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}
		//right of the word
		d_factor = 1;
		for (int i = newWord[Wlen - 1] + 1;
				i <= (newWord[Wlen - 1] + 3) && i < 15; i++) {
			if (board.getBoardValue(newWord[1], i) == 0) //no letter in this box
					{
				if (board.getMultiplierLetter(newWord[1], i) == 2)
					perm += d_factor * 0.4;
				else if (board.getMultiplierLetter(newWord[1], i) == 3)
					perm += d_factor * 0.8;
				else if (board.getMultiplierWord(newWord[1], i) == 2)
					perm += d_factor * 1.2;
				else if (board.getMultiplierWord(newWord[1], i) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}
		//under the word
		d_factor = 1;
		for (int i = newWord[1] + 1; i <= (newWord[1] + 3) && i < 15; i++) {
			for (int j = newWord[2]; j <= newWord[Wlen - 1]; j++) {
				if (board.getBoardValue(i, j) == 0)	//no letter in this box
						{
					if (board.getMultiplierLetter(i, j) == 2)
						perm += d_factor * 0.4;
					else if (board.getMultiplierLetter(i, j) == 3)
						perm += d_factor * 0.8;
					else if (board.getMultiplierWord(i, j) == 2)
						perm += d_factor * 1.2;
					else if (board.getMultiplierWord(i, j) == 3)
						perm += d_factor * 1.6;
				} else
					n -= 0.02;
				d_factor -= 0.3;
			}
		}
		//above the word
		d_factor = 1;
		for (int i = newWord[1] - 1; i >= (newWord[1] - 3) && i >= 0; i--) {
			for (int j = newWord[2]; j <= newWord[Wlen - 1]; j++) {
				if (board.getBoardValue(i, j) == 0)	//no letter in this box
						{
					if (board.getMultiplierLetter(i, j) == 2)
						perm += d_factor * 0.4;
					else if (board.getMultiplierLetter(i, j) == 3)
						perm += d_factor * 0.8;
					else if (board.getMultiplierWord(i, j) == 2)
						perm += d_factor * 1.2;
					else if (board.getMultiplierWord(i, j) == 3)
						perm += d_factor * 1.6;
				} else
					n -= 0.02;
				d_factor -= 0.3;
			}
		}
	}
//vertial word
	else {
		//above the word
		for (int i = newWord[2] - 1; i >= (newWord[2] - 3) && i >= 0; i--) {
			if (board.getBoardValue(i, newWord[1]) == 0)//no letter in this box
					{
				if (board.getMultiplierLetter(i, newWord[1]) == 2)
					perm += d_factor * 0.4;
				else if (board.getMultiplierLetter(i, newWord[1]) == 3)
					perm += d_factor * 0.8;
				else if (board.getMultiplierWord(i, newWord[1]) == 2)
					perm += d_factor * 1.2;
				else if (board.getMultiplierWord(i, newWord[1]) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}
		//under of the word
		d_factor = 1;
		for (int i = newWord[Wlen - 1] + 1;
				i <= (newWord[Wlen - 1] + 3) && i < 15; i++) {
			if (board.getBoardValue(i, newWord[1]) == 0)//no letter in this box
					{
				if (board.getMultiplierLetter(i, newWord[1]) == 2)
					perm += d_factor * 0.4;
				else if (board.getMultiplierLetter(i, newWord[1]) == 3)
					perm += d_factor * 0.8;
				else if (board.getMultiplierWord(i, newWord[1]) == 2)
					perm += d_factor * 1.2;
				else if (board.getMultiplierWord(i, newWord[1]) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}

		//right to  the word
		d_factor = 1;
		for (int i = newWord[1] + 1; i <= (newWord[1] + 3) && i < 15; i++) {
			for (int j = newWord[2]; j <= newWord[Wlen - 1]; j++) {
				if (board.getBoardValue(j, i) == 0)	//no letter in this box
						{
					if (board.getMultiplierLetter(j, i) == 2)
						perm += d_factor * 0.4;
					else if (board.getMultiplierLetter(j, i) == 3)
						perm += d_factor * 0.8;
					else if (board.getMultiplierWord(j, i) == 2)
						perm += d_factor * 1.2;
					else if (board.getMultiplierWord(j, i) == 3)
						perm += d_factor * 1.6;
				} else
					n -= 0.02;
				d_factor -= 0.3;
			}
		}
		//left to the word
		d_factor = 1;
		for (int i = newWord[1] - 1; i >= (newWord[1] - 3) && i >= 0; i--) {
			for (int j = newWord[2]; j <= newWord[Wlen - 1]; j++) {
				if (board.getBoardValue(j, i) == 0)	//no letter in this box
						{
					if (board.getMultiplierLetter(j, i) == 2)
						perm += d_factor * 0.4;
					else if (board.getMultiplierLetter(j, i) == 3)
						perm += d_factor * 0.8;
					else if (board.getMultiplierWord(j, i) == 2)
						perm += d_factor * 1.2;
					else if (board.getMultiplierWord(j, i) == 3)
						perm += d_factor * 1.6;
				} else
					n -= 0.02;
				d_factor -= 0.3;
			}
		}

	}
	return -perm;
}
vector<Move> Heuristic::getAllMoves() {
	vector<Move> v;
	return v;
}
char Heuristic::getChange(Player& p) {
	for (int i = mostUsedLetters.size() - 1; i >= 0; --i)
		if (p.gitTie(mostUsedLetters[i] - st))
			return mostUsedLetters[i];

}
