
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

#include"../Bag/Bag.h"
#include"../Judge/Judge.h"
#include"../Board/Board.h"
#include "../Dictionary/dictionary.h"
using namespace std;
const int   m_bogowinArrayWidth = 602;
const int m_bogowinArrayHeight = 94;
float m_bogowin[m_bogowinArrayWidth][m_bogowinArrayHeight];

bool loadBogowin(const string &filename)
{
	for (int i = 0; i < m_bogowinArrayWidth; ++i)
		for (int j = 0; j < m_bogowinArrayHeight; ++j)
			m_bogowin[i][j] = 0;

	ifstream file(filename.c_str());

	if (!file.is_open())
	{
		cout << "Could not open " << filename << " to load bogowin heuristic" << endl;
		return false;
	}

	while (!file.eof())
	{
		int lead, unseen;
		double wins;

		file >> lead;
		file >> unseen;
		file >> wins;

		m_bogowin[lead + 300][unseen] = wins;
	}

	file.close();
	return true;
}

///// for riham 
char  getChange(Player ana) {
	return 'A';
}

void  random_rack(Bag & bag, Player & opponent) {
	srand(time(NULL));
	int tot = bag.bagLen();
	while (opponent.getTotalTies() < 7 && tot) {	////// for omnia
		int r = rand() % 27;
		while (!bag.getTieCount(r)) {	//// for omnia
			r = rand() % 27;
		}
		bag.removeTie(r);
		tot--;
		opponent.addTie(r);
	}

}
vector<Move> getAllMoves(Player& p,Board board , dictionary dic ) {
	dic.execute(board, p.getTieStr());
	vector<Move> v = dic.getVector();
	return v;
}

void  change(Bag & bag, Player & ply, vector<char> tiles) {
	
	srand(time(NULL));
	int tot = bag.bagLen();
	for (int i = 0; i < tiles.size(); ++i) {
		int r = rand() % 27;
		while (!bag.getTieCount(r)) {	//// for omnia
			r = rand() % 27;
		}
		bag.removeTie(r);
		tot--;
		ply.addTie(r);
	}
	for (char tile : tiles) {
		bag.addTie((int)(tile - 'A'));
	}
}

int simulate(Board   & boardCopy, Player & anaCopy,Player & opponentCopy, Bag & bagCopy, dictionary dic, Judge j ) {
    int score = 0;
    if (j.isClosed(boardCopy))
        return score;
    random_rack(bagCopy, opponentCopy);
    vector<Move> moves = getAllMoves(opponentCopy, boardCopy, dic);
    if (moves.size() == 0) {
        Move move;
        move.tiles.push_back(getChange(opponentCopy));
        change(bagCopy, opponentCopy, move.tiles);
    } else {
        Move move = getBest(moves);
        score -= j.applyMove(move, boardCopy, anaCopy, bagCopy);

    }
    if (j.isClosed(boardCopy))
        return score;
    random_rack(bagCopy, anaCopy);
    moves = getAllMoves(anaCopy, boardCopy, dic);
    if ((int) moves.size() == 0) {
        Move move;
        move.tiles.push_back(getChange(anaCopy));
        change(bagCopy, anaCopy, move.tiles);
    } else {
        Move move = getBest(moves);
        score += j.applyMove(move, boardCopy, anaCopy, bagCopy);
    }
    return score;
}

Move nextPlay( vector<Move> plays, Board board, Bag bag,
	Player ana, Judge J, Player opponent, dictionary dic,vector<float>value) {
	if (!(int) plays.size()) {
		Move m;
		// omnia 
		m.tiles.push_back(getChange(ana));
		return m;
	}
	Player anaCopy(ana.getPlayerID());
	Player  opponentCopy(opponent.getPlayerID());
	Bag bagCopy = bag;
	Board boardCopy = board;
	int size = (int) plays.size();
	int idx = 0;
	float mx = -1e9;
	for (int i = 0; i < plays.size(); ++i) {
		for (int i = 0; i < 27; ++i) {
			anaCopy.addValue(ana.getValue(i), i);
		}
		for (int i = 0; i < 27; ++i) {
			opponentCopy.addValue(opponent.getValue(i), i);
		}
		float score = J.applyMove(plays[i], boardCopy, anaCopy, bagCopy);	/////for omnia
		int reminder = 100 - anaCopy.getTotalTies() - boardCopy.tiesCount();
		for (int k = 0; k < 300; ++k) {
			score += simulate(boardCopy, anaCopy,
				opponentCopy, bagCopy,dic,J);
			score += getFromHurastic(anaCopy);
		}
		score /= 300;
		int intScore = (int)round(score);
		if (intScore > 300)
			intScore = 300;
		if (intScore < -300)
			intScore = -300;
		if (mx < m_bogowin[intScore][reminder])
			mx = m_bogowin[intScore][reminder], idx = i;
		else if (mx == m_bogowin[intScore][reminder]) {
			if (value[i] < value[idx])
				idx = i;
		
		}
	}
	return plays[idx];
}

int main() {
	loadBogowin("bogowin.txt");

}
