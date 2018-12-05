/*
 * Heuristic.cpp
 *
 *  Created on: Nov 25, 2018
 *      Author: ghada
 */
#include<bits/stdc++.h>
#include "Heuristic.h"
using namespace std;
Heuristic::Heuristic(Board& b, dictionary& d, Bag& bg, Judge& j, Player& p,
		Player& p2) {
	// TODO Auto-generated constructor stub
	board = &b;
	dec = &d;
	bag = &bg;
	J = (&j);
	state = 0;
	player = &p;
	opponent = &p2;
	//The weights for the first occurence of a letter
	// * means blank
	map<char, double> LL1 { { 'a', 1.0 }, { 'b', -3.5 }, { 'c', -0.5 }, { 'd',
			0.0 }, { 'e', 4.0 }, { 'f', -2.0 }, { 'g', -2.0 }, { 'h', 0.5 }, {
			'i', -0.5 }, { 'j', -3.0 }, { 'k', -2.5 }, { 'l', -1.0 }, { 'm',
			-1.0 }, { 'n', 0.5 }, { 'o', -1.5 }, { 'p', -1.5 }, { 'q', -11.5 },
			{ 'r', 1.5 }, { 's', 7.5 }, { 't', 0.0 }, { 'u', -3.0 },
			{ 'v', -5.5 }, { 'w', -4.0 }, { 'x', 3.5 }, { 'y', -2.0 }, { 'z',
					2.0 }, { '*', 24.5 } // '*' means blank
	};

	//Duplicate weights
	map<char, double> LL2 { { 'a', -3.0 }, { 'b', -3.0 }, { 'c', -3.5 }, { 'd',
			-2.5 }, { 'e', -2.5 }, { 'f', -2.0 }, { 'g', -2.5 }, { 'h', -3.5 },
			{ 'i', -4.0 }, { 'j', 0.0 }, { 'k', 0 }, { 'l', -2.0 },
			{ 'm', -2.0 }, { 'n', -2.5 }, { 'o', -3.5 }, { 'p', -2.5 },
			{ 'q', 0 }, { 'r', -3.5 }, { 's', -4.0 }, { 't', -2.5 },
			{ 'u', -3.0 }, { 'v', -3.5 }, { 'w', -4.5 }, { 'x', 0 },
			{ 'y', -4.5 }, { 'z', 0 }, { '*', 15.0 } };
	/*j,k,q,x,z mknsh lehm rkm w 5lthm bzero,mmkn ab2a ashelhm mn lmap dh
	 w a5od rkmhm mn fo2 k2nhm msh duplicate!
	 */
	L1 = LL1;
	L2 = LL2;
	startW[0] = w[0] = 0.3;
	startW[1] = w[1] = 0.7;
	startW[2] = w[2] = 0.2;
	startW[3] = w[3] = 0.1;
	startW[4] = w[4] = 0.4;

}

Heuristic::~Heuristic() {
	// TODO Auto-generated destructor stub
}
void Heuristic::setBoard(Board& b) {
	board = &b;
}
void Heuristic::setBag(Bag& b) {
	bag = &b;
}

void Heuristic::setPlayer(Player& p) {
	player = &p;
}

bool Heuristic::filterPossibles(string s, int cur[]) {
	int freq[27];
	memset(freq, 0, sizeof(freq));
	for (char j : s)
		if (j >= 'A' && j <= 'Z')
			freq[j - st]++;
		else
			freq[26]++;
	for (int j = 0; j < 27; ++j)
		if (((freq[j] < cur[j] || freq[j] > cur[j] + bag->getTieCount(j))))
			return false;

	return true;

}
///implement for omnia
// btgeeb kol el strings eli mn 7 chars eli law et7tet fl board t3ml bingo
vector<pair<string, int>> Heuristic::getPossibleBingo(string str, int cur[]) {
	while (str.size() < 7)
		str += 'e';
	dec->execute(*board, str, 100);
	vector<Move> v = dec->getVector();
	vector<pair<string, int> > ret;
	for (int i = 0; i < (int) v.size(); ++i) {
		if (v[i].word.size())
			continue;
		if (!filterPossibles(v[i].playedWord, cur))
			continue;
		//////////////////////////////////////////////////////
		// h7sb el score
		int score = J->applyMoveNoChange(v[i], *board, *bag);
		pair<string, int> p = { v[i].playedWord, score };
		ret.push_back(p);
	}
	return ret;

}

double Heuristic::calcProbability(int freq[], int score, int cur[]) {

	double letterP = 1;
	int cnt = 0;
	for (int i = 0; i < 27; ++i) {
		if (cur[i] >= freq[i])
			continue;
		// cur[i] hya el 7rof eli m3aya
		freq[i] -= cur[i];
		cnt += freq[i];
		letterP *= J->pascal[bag->getTieCount(i)][freq[i]];
	}
	letterP /= (J->pascal[bag->bagLen()][cnt] * 1.0);
// multiply by 2.5 if the score isn't calculated for the board
	return letterP * (50 + score);
}
double Heuristic::expectedBingoMe(Move& move) {
	string word = move.word;
	if (move.playedWord.size() == 7)
		return 0.0;
	int freq[27], cur[27];
	memset(cur, 0, sizeof(cur));
	for (int i = 0; i < (int) word.size(); ++i)
		if (word[i] == 'e')
			cur[26]++;
		else
			cur[word[i] - st]++;

	vector<pair<string, int>> possible = getPossibleBingo(word, cur);
	//possible = filterPossibles(possible, cur);
	double p = 0;
	for (auto &i : possible) {
		memset(freq, 0, sizeof(freq));
		for (int j = 0; j < (int) i.first.size(); ++j)
			if (i.first[j] >= 'A' && i.first[j] <= 'Z')
				freq[i.first[j] - st]++;
			else
				freq[26]++;

		// calculate the expected number of the score to make this word
		p += calcProbability(freq, i.second, cur);
	}
	return p; // multiply  p * 0.8 assuming prob of bingo in the next play will decrease by 0.2
}
double Heuristic::QwithU(string m) {
	int cntQ = 0;
	int cntU = 0;

	for (char i : m)
		if (i == 'Q')
			cntQ++;
		else if (i == 'U')
			cntU++;
	if (cntQ && cntU)
		return 30.0;
	else
		return 0.0;
}
double Heuristic::expectedBingoOpponent() {
	string s = opponent->getTieStr();
	int cur[27];
	memset(cur, 0, sizeof(cur));
	for (int i = 0; i < (int) s.size(); ++i)
		if (s[i] == 'e')
			cur[26]++;
		else
			cur[s[i] - 'A']++;
	vector<pair<string, int>> possible = getPossibleBingo(s, cur);
	int mx = 0;
	for (int i = 0; i < (int) possible.size(); ++i) {
		mx += possible[i].second;
	}
	return -mx * 1.0 / ((int) possible.size() * 1.0);
// eb3ty el mx
//////////////// mfrod ab3t el exScore
}

double Heuristic::RackLeaveScore(string C) {

	double score = 0.0;

	char x;
	map<char, double> m;  // The accumulative weight for each letter in the rack
	int v = 0, c = 0; //the number of vowels and constants

	for (int i = 0; i < (int) C.length(); i++) {
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
vector<Move> Heuristic::getAllMoves() {
	dec->execute(*board, player->getTieStr());
	vector<Move> v = dec->getVector();
	return v;
}
void Heuristic::getChange(char* ex) {
	int size = bag->bagLen() - 7;
	size = min(size, 4);
	ex[0] = '\0';
	if (size <= 0)
		return;
	int exIdx = 0;
	for (int i = 0; i < 26 && exIdx < size; ++i)
		if (player->getTie(i) > 2)
			ex[exIdx++] = char(i + 'A');
	if (exIdx == size)
		return;
	if (player->getTie('Q' - 'A') && !player->getTie('U' - 'A'))
		ex[exIdx++] = 'Q';
	if (exIdx++ == size)
		return;
	string rack = player->getTieStr();
	pair<double, int> weight[7];
	sort(rack.begin(), rack.end());
	for (int i = 0; i < (int) rack.size(); ++i) {
		if (rack[i] == 'e')
			continue;
		char c = tolower(rack[i]);
		if (i > 0 && rack[i] == rack[i - 1])
			weight[i].first = L2[c];
		else
			weight[i].first = L1[c];
		weight[i].second = i;
	}
	sort(weight, weight + 7);
	int idx = 0;
	while (exIdx++ < size && idx < (int) rack.size())
		ex[exIdx++] = rack[weight[idx++].second];

	return;

}

double Heuristic::getHeu(Move& m) {
	// lma omnia trod 3alia hashof expented bingo opponenet
	if (opponent->getScore() - player->getScore() > 60)
		w[3] = startW[3] + 0.4;
	else
		w[3] = startW[3];
	if (bag->bagLen() < 11)
		w[3] = startW[3] + 0.3;

	double num = w[0] * expectedBingoMe(m) + w[1] * RackLeaveScore(m.word)
			+ w[2] * QwithU(m.playedWord) + w[3] * DefensiveStrategy(m)
			+ w[4] * expectedBingoMe(m);
	return num;
}

double Heuristic::qSticking(Move& mv) {
	if (bag->bagLen() > 7)
		return 0.0;
	if (!bag->getTieCount('Q' - 'A') && !bag->getTieCount('V' - 'A'))
		return 0.0;
	string rack = "";
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < (bag->getTieCount(i)); ++j)
			rack += char(i + 'A');
	if (bag->getTieCount(26))
		rack += 'e';

	Board newB = *board;
	Player b = *player;
	J->applyMove(mv, newB, b, *bag);
	dec->execute(newB, rack, 100);
	vector<Move> tmp = dec->getVector();
	bool fnd1 = false;
	bool fnd2 = true;
	for (int j = 0; j < (int) tmp.size() && !(fnd1 & fnd2); ++j) {
		for (int k = 0; k < (int) tmp[j].playedWord.size(); ++k)
			if (tmp[j].playedWord[k] == 'Q')
				fnd1 = true;
			else if (tmp[j].playedWord[k] == 'V')
				fnd2 = true;

	}
	if (!fnd1 && !fnd2)
		return 100.0;
	if (!fnd1)
		return 50.0;
	if (!fnd2)
		return 25.0;
	return 0.0;

}

//----------------------->will be modified later depending on what will bs sent
double Heuristic::DefensiveStrategy(Move move) {
	double perm = 0.0;
	vector<int> newWord;
	newWord.push_back(move.direction);
	if (newWord[0] == 0) {
		newWord.push_back(move.y);
		for (int i = 0; i < (int) move.word.size(); ++i)
			newWord.push_back(move.x + i);
	} else {
		newWord.push_back(move.x);
		for (int i = 0; i < (int) move.word.size(); ++i)
			newWord.push_back(move.y + i);
	}

	int Wlen = newWord.size();
	/*
	 newWord{0 if horizontal 1 if vertical,index 1 is the row # in case of horizantal
	 and column # in case of vertical word,
	 rest of number are column indexes in case of horizontal
	 and row indexes in case of vertical
	 */
	double d_factor = 1;
	double n = 1;
//horizontal word
	if (newWord[0] == 0) {
		//search horizontally--left of the word
		for (int i = newWord[2] - 1; i >= (newWord[2] - 3) && i >= 0; i--) {
			if (board->getBoardValue(newWord[1], i) == 0) //no letter in this box
					{
				if (board->getMultiplierLetter(newWord[1], i) == 2)
					perm += d_factor * 0.4;
				else if (board->getMultiplierLetter(newWord[1], i) == 3)
					perm += d_factor * 0.8;
				else if (board->getMultiplierWord(newWord[1], i) == 2)
					perm += d_factor * 1.2;
				else if (board->getMultiplierWord(newWord[1], i) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}
		//right of the word
		d_factor = 1;
		for (int i = newWord[Wlen - 1] + 1;
				i <= (newWord[Wlen - 1] + 3) && i < 15; i++) {
			if (board->getBoardValue(newWord[1], i) == 0) //no letter in this box
					{
				if (board->getMultiplierLetter(newWord[1], i) == 2)
					perm += d_factor * 0.4;
				else if (board->getMultiplierLetter(newWord[1], i) == 3)
					perm += d_factor * 0.8;
				else if (board->getMultiplierWord(newWord[1], i) == 2)
					perm += d_factor * 1.2;
				else if (board->getMultiplierWord(newWord[1], i) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}
		//under the word
		d_factor = 1;
		for (int i = newWord[1] + 1; i <= (newWord[1] + 3) && i < 15; i++) {
			for (int j = newWord[2]; j <= newWord[Wlen - 1]; j++) {
				if (board->getBoardValue(i, j) == 0)	//no letter in this box
						{
					if (board->getMultiplierLetter(i, j) == 2)
						perm += d_factor * 0.4;
					else if (board->getMultiplierLetter(i, j) == 3)
						perm += d_factor * 0.8;
					else if (board->getMultiplierWord(i, j) == 2)
						perm += d_factor * 1.2;
					else if (board->getMultiplierWord(i, j) == 3)
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
				if (board->getBoardValue(i, j) == 0)	//no letter in this box
						{
					if (board->getMultiplierLetter(i, j) == 2)
						perm += d_factor * 0.4;
					else if (board->getMultiplierLetter(i, j) == 3)
						perm += d_factor * 0.8;
					else if (board->getMultiplierWord(i, j) == 2)
						perm += d_factor * 1.2;
					else if (board->getMultiplierWord(i, j) == 3)
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
			if (board->getBoardValue(i, newWord[1]) == 0)//no letter in this box
					{
				if (board->getMultiplierLetter(i, newWord[1]) == 2)
					perm += d_factor * 0.4;
				else if (board->getMultiplierLetter(i, newWord[1]) == 3)
					perm += d_factor * 0.8;
				else if (board->getMultiplierWord(i, newWord[1]) == 2)
					perm += d_factor * 1.2;
				else if (board->getMultiplierWord(i, newWord[1]) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}
		//under of the word
		d_factor = 1;
		for (int i = newWord[Wlen - 1] + 1;
				i <= (newWord[Wlen - 1] + 3) && i < 15; i++) {
			if (board->getBoardValue(i, newWord[1]) == 0)//no letter in this box
					{
				if (board->getMultiplierLetter(i, newWord[1]) == 2)
					perm += d_factor * 0.4;
				else if (board->getMultiplierLetter(i, newWord[1]) == 3)
					perm += d_factor * 0.8;
				else if (board->getMultiplierWord(i, newWord[1]) == 2)
					perm += d_factor * 1.2;
				else if (board->getMultiplierWord(i, newWord[1]) == 3)
					perm += d_factor * 1.6;
			} else
				n -= 0.02;
			d_factor -= 0.3;
		}

		//right to  the word
		d_factor = 1;
		for (int i = newWord[1] + 1; i <= (newWord[1] + 3) && i < 15; i++) {
			for (int j = newWord[2]; j <= newWord[Wlen - 1]; j++) {
				if (board->getBoardValue(j, i) == 0)	//no letter in this box
						{
					if (board->getMultiplierLetter(j, i) == 2)
						perm += d_factor * 0.4;
					else if (board->getMultiplierLetter(j, i) == 3)
						perm += d_factor * 0.8;
					else if (board->getMultiplierWord(j, i) == 2)
						perm += d_factor * 1.2;
					else if (board->getMultiplierWord(j, i) == 3)
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
				if (board->getBoardValue(j, i) == 0)	//no letter in this box
						{
					if (board->getMultiplierLetter(j, i) == 2)
						perm += d_factor * 0.4;
					else if (board->getMultiplierLetter(j, i) == 3)
						perm += d_factor * 0.8;
					else if (board->getMultiplierWord(j, i) == 2)
						perm += d_factor * 1.2;
					else if (board->getMultiplierWord(j, i) == 3)
						perm += d_factor * 1.6;
				} else
					n -= 0.02;
				d_factor -= 0.3;
			}
		}

	}
	return -n * perm;
}

void Heuristic::Slowendgame(vector<Move>& possibleMoves, string oPPrack) {

	int mcount = possibleMoves.size();
	string word1, word2;
	int wlen, wlen2;
	bool x;
	int score;
	std::size_t found;
// a map of the characters with the opponent to easily check which chars he has
	map<char, int> Or;
	for (int i = 0; i < (int) oPPrack.size(); ++i)
		Or.insert( { oPPrack[i], 0 });

	for (int i = 0; i < mcount - 1; ++i) {
		wlen = possibleMoves[i].word.length();
		score = J->applyMoveNoChange(possibleMoves[i], *board, *bag);
		possibleMoves[i].heuristicValue += score
				/ possibleMoves[i].playedWord.length();
		for (int j = i + 1; j < mcount; ++j) {
			//which word is longer
			wlen2 = possibleMoves[j].word.length();
			if (wlen > wlen2) {
				word1 = possibleMoves[i].word;
				word2 = possibleMoves[j].word;
				x = true; // the ith word is the greater  
			} else if (wlen2 > wlen) {
				word2 = possibleMoves[i].word;
				word1 = possibleMoves[j].word;
				x = false; //jth word is the greater
			}

			found = word1.find(word2);  // check it word2 is subset of word1
			if (found == 0) {
				//check if the other chars are with the opponent too
				for (int ww = found + word2.length(); ww < (int) word1.length();
						++ww)
					// check if the letters are with the opponent
					if (Or.count(word1[ww])) {

						if (x) {
							possibleMoves.erase(possibleMoves.begin() + j);
							possibleMoves[i].heuristicValue += 10;
						} else { //remove the ith word and break from the j loop
							possibleMoves.erase(possibleMoves.begin() + i);
							possibleMoves[j].heuristicValue += 10;
							j = mcount;  // to break the jth loop
						}
					}

				break;
			}

		}
	}

	std::sort(possibleMoves.begin(), possibleMoves.end());
}
