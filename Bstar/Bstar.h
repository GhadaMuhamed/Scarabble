#include <iostream>
using namespace std;
#include <vector>
#include <tuple>
#include <map>
#include "../Move/Move.h"
#include "../Heuristic/Heuristic.h"
#include "../Judge/Judge.h"
#include "../Board/Board.h"
#include "../Bag/Bag.h"

struct node
{
	int optim; ////////////initially ??????!!!!!!!!!!!!
	int pessim;
	node* parent;
	Move mv;
	vector<node>children;

}; 

class Bstar {

	public :
		node b_star(vector<Move> words, Board board, Player player1,
			Player player2, Bag bg, dictionary & dic, Heuristic & heu);
		void getBestAndAlternate(node curr, int& maxOptim, int& maxPessim, node& best, node& altern);

};
