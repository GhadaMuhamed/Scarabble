#include "learnedWeights.h"

learnedWeights::learnedWeights()
{
	opp_moves = 0, my_moves = 0;

	ifstream wtFile;
	wtFile.open("myfile.txt");
	int i;
	for (i = 0; i < 3; ++i) wtFile >> W[i];
	for (i = 0; i < 4; ++i) wtFile >> Statistics[i];
	wtFile.close();
}

void learnedWeights::newmove(int player, Move m, Board B,Bag bag,Judge j) {
	//This is my turn
	string line= (!m.direction)? B.getRow(m.x): B.getCoulmn(m.y);
		
	
	if (player == 0) {
		if (m.playedWord == "")agent[2] += 1;//rack evaluation
		else
		{
			if (m.playedWord.size() == 7)agent[0] += 50;//bingo score
			agent[3] += j.applyMoveNoChange(m, B, bag);//total score of this move
			agent[1] += calculate_prem(m,B,bag,line);//prem score
			
			++my_moves;
		}

	}
	//This is the opponent's turn
	else {
		if (m.playedWord == "")opponent[2] += 1;//rack evaluation
		else
		{
			if (m.playedWord.size() == 7)opponent[0] += 50;//bingo score
			opponent[3] += j.applyMoveNoChange(m, B, bag);//total score of this move
			agent[1] += calculate_prem(m, B, bag, line);//prem score
			++opp_moves;
	}

}

void learnedWeights::updateWeights(int winner) {
	ofstream wtFile;

	wtFile.open("myfile.txt");
	
	//I am the winner
	/*
	if (winner == 0) {
		Statistics[0] += agent[0];  
		Statistics[1] += agent[1];
		Statistics[2] += agent[2];
		Statistics[3] += my_moves;
	}
	// The opponent is the winner
	else {}*/
	if (winner == 1) {
		Statistics[0] += opponent[0] / opponent[3];
		Statistics[1] += opponent[1] / opponent[3];
		Statistics[2] += opponent[2] / opp_moves;
		Statistics[3] += opp_moves;

	}
	// write the updated weights to the file
		
	wtFile << (Statistics[0])  << " " 
		<< (Statistics[1]) <<" "
		<<(Statistics[2])  <<" "
		<<(Statistics[3])<< endl;


	wtFile.close();
	return;
}

int learnedWeights:: calculate_prem(Move m, Board B,Bag bag,string l) {
	int points = 0;
	string line = "";
	vector<pair<int, int>> positions;
	line = (!m.direction) ? B.getHorizontalWord(m.x, m.y): B.getVerticalWord(m.x, m.y);
	int y;
	if (!m.direction) {
		 y=m.y;

		for (int i = y; i < 15 ||(positions.size() ==m.playedWord.size()); ++i) {

			if (B.getBoardValue(m.x,i) == -1) positions.push_back(make_pair(m.x,i));
		}

	}
	else
	{
		y = m.x;	
		for (int x = y; x < 15 || (positions.size() == m.playedWord.size()); ++x) {

			if (B.getBoardValue( x,m.y) == -1) positions.push_back(make_pair( x,m.y));
		}
	}

	for (int k = 0; k < positions.size();++k) {
	
		points += (  B.getMultiplierLetter(positions[k].first, positions[k].second)   *	bag.getTieScore(m.playedWord[k]));
		if (B.getMultiplierWord(positions[k].first, positions[k].second) > 1) {
		
			string word = ""; int score = 0;
			word = B.getHorizontalWord(positions[k].first, positions[k].second);
			for (char e:word) score += bag.getTieScore(e);

			word = B.getVerticalWord(positions[k].first, positions[k].second);
			for (char e : word) score += bag.getTieScore(e);

			points += (B.getMultiplierWord(positions[k].first, positions[k].second)) * score;
		
		}
	}
	return points;
}


double* learnedWeights::getWeights() {
	return W;
}

learnedWeights::~learnedWeights(){
}
