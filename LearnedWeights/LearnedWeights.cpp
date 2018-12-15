#include "learnedWeights.h"

learnedWeights::learnedWeights()
{
	opp_moves = 0, my_moves = 0;

	ifstream wtFile;
	wtFile.open("myfile.txt");
	int i;
	for (i = 0; i < 3; ++i) wtFile >> W[i];
	wtFile.close();
}

void learnedWeights::newmove(vector<Point>,int player,int total_score,Move m, Board B,Bag bag,Judge j) {
	//This is my turn

	if (player == 0) {
		if (m.playedWord == "")agent[2] += 1;//rack evaluation
		else
		{
			if (m.playedWord.size() == 7)agent[0] += 50;//bingo score
			agent[3] += total_score;//total score of this move
			agent[1] += calculate_prem(positions,B,bag);//prem score

			++my_moves;
		}

	}
	//This is the opponent's turn
	else {
		if (m.playedWord == "")opponent[2] += 1;//rack evaluation
		else
		{
			if (m.playedWord.size() == 7)opponent[0] += 50;//bingo score
			opponent[3] += total_score;//total score of this move
			opponent[1] += calculate_prem(positions, B, bag);//prem score
			++opp_moves;
	}

}
}

void learnedWeights::updateWeights(int winner) {
	ofstream wtFile;

	wtFile.open("myfile.txt");

	//the agent lost
	if (winner == 1) {
		Statistics[0] = opponent[0] / opponent[3];
		Statistics[1] = opponent[1] / opponent[3];
		Statistics[2] = opponent[2] / opp_moves;
		Statistics[3] = opp_moves;

	}
	// write the updated weights to the file

	wtFile << (Statistics[0])  << " "
		<< (Statistics[1]) <<" "
		<<(Statistics[2])  <<" "
		<<(Statistics[3])<< endl;


	wtFile.close();
	return;
}



int learnedWeights:: calculate_prem(vector<Point> positions, Board B,Bag bag) {
	int points = 0;


	for (int k = 0; k < positions.size();++k) {

			if (  B.getMultiplierLetter(positions[k].r, positions[k].c) >1  && B.getBoardValue(positions[k].c,positions[k].c)<100)   points+=  B.getMultiplierLetter(positions[k].r, positions[k].c) *	bag.getTieScore(B.getBoardValue(positions[k].c, positions[k].c));
			if (B.getMultiplierWord(positions[k].r, positions[k].c) > 1) {

				string word = ""; int score = 0;
				int temp_a = B.getBoardValue(positions[k].c, positions[k].c);
				word = B.getHorizontalWord(positions[k].r, positions[k].c);
				if (word.length() > 1) {
					for (char e : word) score += (isupper(e)) ? bag.getTieScore(e - 65) : 0;

					score -= (temp_a < 100) ? bag.getTieScore( temp_a) : 0;
				}

				word = B.getVerticalWord(positions[k].r, positions[k].c);
				if (word.length() > 1) {
					for (char e : word) score += (isupper(e)) ? bag.getTieScore(e - 65) : 0;
					score -= (temp_a < 100) ? bag.getTieScore(temp_a) : 0;
				}

				score += (temp_a < 100) ? bag.getTieScore(temp_a) : 0;
				points += (B.getMultiplierWord(positions[k].r, positions[k].c)) * score;

			}
		}

	return points;
}


double* learnedWeights::getWeights() {
	return W;
}

learnedWeights::~learnedWeights(){
}
