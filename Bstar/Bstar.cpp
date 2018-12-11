#include"Bstar.h"
node Bstar::b_star(vector<Move> words, Board board, Player player1,
	Player player2, Bag bg, dictionary & dic,Heuristic & heu) {
	/*1*/	int depth = 0;
	int maxOptim = 0;
	int maxPess = 0;
	node root;
	root.parent = NULL;
	root.optim = -INFINITY;
	root.pessim = INFINITY;
	node current = root;
	node bestNode;
	node alternate;
	int turn = 0; //zero => my turn else => his turn
				  /////////////////////call dictionary with the turn's char's

	if (!words.size()) {
		Move m;
		heu.setPlayer(player1);
		char* ex = new char[7];
		heu.getChange(ex);
		if (strlen(ex) == 0)
			m.switchMove = true;
		for (int i = 0; i < strlen(ex); ++i)
			m.tiles.push_back(ex[i]);
		node r;
		r.parent = NULL;
		r.optim = 0;
		r.pessim = INFINITY;
		r.mv = m;
		return r;
	}

	Judge jdg;
	Board brd;
	Player plr1(0);
	Player plr2(2);
	brd = board;
	plr1 = player1;
	plr2 = player2;
	//vector<node> arr;
	//vector<Move>word;
	///arr.push_back(root);
	///for (int i = 0; i < sizeof(words); i++)
	///{
	///	node n;
	///	n.mv = words[i];

	///}
	// dictionary(words);
	while (!words.empty())
		/*2*/ {

		if (current.children.empty())
		{
			//map<string, tuple<int, int, char>>::iterator itr;
			int i = 0;
			for (i; i<words.size(); i++) /////////////////////////sizeof ehhh??!!!
			{
				node n;
				n.mv = words[i];
				n.parent = &current;
				//n.word = itr->first;
				if (turn == 0)
				{
					n.optim = jdg.applyMoveNoChange(n.mv, brd, bg); // get cost of the word as optim if it is my turn
																	/////////n.pessim ???
				}
				else if (turn == 1){

					n.optim = -1 * jdg.applyMoveNoChange(n.mv, brd, bg); // get cost of the word as pessim if it is the other's turn
																		 /////////n.optim ???
				}
				current.children.push_back(n);
				current.children.back().parent = &current;

			}
			words.clear();
		}

		while (depth>0)
		{
			/*3*/ getBestAndAlternate(current, maxOptim, maxPess, bestNode, alternate);
			/*4*/ if ((maxOptim<current.pessim) || (maxPess>current.optim))
			{
				current.pessim = -1 * maxOptim;
				current.optim = -1 * maxPess;
			}

			current = *current.parent;
			depth--;
		}
		/*3*/ getBestAndAlternate(current, maxOptim, maxPess, bestNode, alternate);

		/*4*/ if ((maxOptim<current.pessim) || (maxPess>current.optim))
		{
			current.pessim = -1 * maxOptim;
			current.optim = -1 * maxPess;
			//	if (depth > 0)
			//	{
			//		current = *current.parent;
			//		depth--;
			//		///////////////////go to 3 
			//	}
			//	else if(depth==0)
			//	{
			if (bestNode.pessim >= alternate.optim)
				return bestNode;
			//	}
		}

		/*5*/	if (depth == 0)
		{
			if (bestNode.pessim == maxPess)
				current = alternate; //disproveRest
			else
				current = bestNode; //proveBest
		}
		/*6*/	if (depth != 0)
		{
			current = bestNode;
		}

		/*7*/	depth++;
		/////////////////////apply action ???
		if (turn == 0)
			jdg.applyMove(current.mv, brd, plr1, bg);
		else
			jdg.applyMove(current.mv, brd, plr2, bg);
		turn = (turn + 1) % 2;
		if (turn == 0) {
			dic.execute(board, plr1.getTieStr());
			vector<Move> v = dic.getVector();
		}
		else	{
			dic.execute(board, plr1.getTieStr());
			vector<Move> v = dic.getVector();
		}
		/////// go to 2

	}
	return bestNode;
}

void Bstar::getBestAndAlternate(node current, int& maxOptim, int& maxPess, node& bestNode, node& alternate) {

	if ((current.children[0].optim) > (current.children[1].optim))
	{
		bestNode = current.children[0];
		alternate = current.children[1];
	}
	else {
		bestNode = current.children[1];
		alternate = current.children[0];
	}
	if ((current.children[0].pessim) > (current.children[1].pessim))
		maxPess = current.children[0].pessim;
	else
		maxPess = current.children[1].pessim;

	for (int i = 2; i < current.children.size(); i++)
	{
		if ((current.children[i].optim) >(bestNode.optim))
		{
			alternate = bestNode;
			bestNode = current.children[i];
		}
		else if (((current.children[i].optim) > (alternate.optim)) && (current.children[i].optim != bestNode.optim))
			alternate = current.children[i];


		if ((current.children[i].pessim) > maxPess)
			maxPess = current.children[i].pessim;
	}
	maxOptim = bestNode.optim;
}
