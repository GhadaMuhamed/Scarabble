/*
 * Communcation.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: ghada
 */

#include "Communcation.h"
#include "../source.cpp"
Communcation::Communcation() {
<<<<<<< HEAD
	board = player1 = player2 = judge = bag = dic = heu = NULL;
}
void Communcation::start(commToImp c) {
	// start or disconnect
	if (c.Msgtype == 1) {
		bag = new Bag();
		board = new Board(c.Board_from_server);
		player1 = new Player(0);
		player2 = new Player(1);
		player2->addScore(c.opponent_score);
		player1->addScore(c.Player_score);
		judge = new Judge(c.our_remaining_time, c.total_remaining_time);
		dic = new dictionary("sowpods.txt");
		heu = new Heuristic(*board, *dic, *bag, *judge, *player1);
		for (int i = 0; i < 7; ++i) {
			if (c.move.tiles[i] == -1)
				break;
			if (c.move.tiles[i] != 99)
				player1->addTie(c.move.tiles[i]), bag->removeTie(
						c.move.tiles[i]);
			else
				player1->addTie(26), bag->removeTie(26);
		}
		for (int i = 0; i < BOARD_SIZE; ++i)
			for (int j = 0; j < BOARD_SIZE; ++j)
				if (c.Board_from_server[i][j] >= 0
						&& c.Board_from_server[i][j] < 26)
					bag->removeTie(c.Board_from_server[i][j]);
	}
	if (c.order == 1) {
		if (c.Msgtype != 4) {
			dic->execute(*board, player1->getTieStr());
			Move best = nextPlay(*heu, dic->getVector(), *board, *bag, *player1,
					*judge);
			commToImp ret;

			if (best.switchMove)
				ret.Msgtype = 2;
			else if (best.tiles.size())
				ret.Msgtype = 3;
			else
				ret.Msgtype = 4;
			ret.move = castToServerMove(best);
			// return ret

		} else {
			commToImp obj;
			if (checkStrings(c.move)) {
				obj.Msgtype = 5;
				Move mv = castToMove(c.move);
				judge->applyMove(mv, *board, *player2, *bag);
				for (int i = 0; i < 7; ++i)
					if (c.move.tiles[i] == -1)
						break;
					else if (c.move.tiles[i] < 26)
						bag->removeTie(c.move.tiles[i]);
					else
						bag->removeTie(27);
=======
	// TODO Auto-generated constructor stub
	board = nullptr;

}
void Communcation::start(commToImp c) {
	// start or disconnect
	if (c.Msgtype == 1 || c.Msgtype == 12) {
//		board = new Board(c.Board_from_server);
>>>>>>> ee30d543dd5da180e0d541927cfbd2d2f03d35dd

			} else
				obj.Msgtype = 6;

		}
		if (c.Msgtype == 8) {
			//call ui
		}
	} else if (c.order == 2) {
		if (c.Msgtype == 3 || c.Msgtype == 5) {
			for (int i = 0; i < 7; ++i) {
				if (c.move.tiles[i] == -1)
					break;
				if (c.move.tiles[i] == 90)
					player1->addTie(26), bag->removeTie(26);
				else
					player1->addTie(c.move.tiles[i]), bag->removeTie(
							c.move.tiles[i]);
			}
		}
		if (c.Msgtype == 5) {
			// call ui
		}
	}

}

bool Communcation::checkStrings(Move_to_from_server mv) {
	int stR = mv.row;
	int stC = mv.column;
	int direc = mv.Directon;

	int len = 0;
	string played = "";
	for (int i = 0; i < 7; ++i)
		if (mv.tiles[i] == -1)
			break;
		else
			len++, played += char(mv.tiles[i] + 'A');

//ofoky
	if (!direc) {
		string s1 = board->getHorizontalWord(stR, stC - 1);
		string s2 = board->getHorizontalWord(stR, stC + len);
		string horz = s1;
		horz += played;
		horz += s2;
		if (!dic->check(horz))
			return false;
		for (int i = 0; i < played.size(); ++i) {
			string ver = board->getVerticalWord(stR - 1, stC);
			ver += played[i];
			ver += board->getVerticalWord(stR + 1, stC);
			if (!dic->check(ver))
				return false;
			stC++;
		}
	} else {
		string ver = board->getVerticalWord(stR - 1, stC);
		ver += played;
		ver += board->getVerticalWord(stR + len, stC);
		if (!dic->check(ver))
			return false;
		for (int i = 0; i < played.size(); ++i) {
			string horz = board->getHorizontalWord(stR, stC - 1);
			horz += played[i];
			horz += board->getHorizontalWord(stR, stC + 1);
			if (!dic->check(horz))
				return false;
			stR++;
		}

	}
	return true;
}
Move Communcation::castToMove(Move_to_from_server & serverMove) {
	Move move;
	move.direction = serverMove.Directon;
	string s = "";
	for (int i = 0; i < 7; ++i)
		if (serverMove.tiles[i] == -1)
			break;
		else
			s += char(serverMove.tiles[i] + 'A');
	move.playedWord = s;
	move.x = serverMove.row;
	move.y = serverMove.column;
	return move;

}
Move_to_from_server Communcation::castToServerMove(Move & move) {

	Move_to_from_server serverMove;
	serverMove.Directon = move.direction;
	serverMove.column = move.y;
	serverMove.row = move.x;
	int arr[27];
	for (int i = 0; i < 27; ++i)
		arr[i] = player1->getTie(i);
	for (int i = 0; i < 7; ++i)
		if (move.tiles.size() < i)
			serverMove.tiles[i] = (
					move.tiles[i] < 26 ? int(move.tiles[i] - 'A') : 99);
		else if (!move.tiles.size() && move.playedWord.size() < i) {
			if (arr[move.playedWord[i] - 'A']) {
				serverMove.tiles[i] = int(move.playedWord[i] - 'A');
				arr[move.playedWord[i] - 'A']--;
			} else
				serverMove.tiles[i] = int(move.playedWord[i] - 'A') + 100;

		} else
			serverMove.tiles[i] = -1;
	return serverMove;
}
Communcation::~Communcation() {
	if (board != nullptr)
		delete board;
	if (player1 != NULL)
		delete player1;
	if (judge != NULL)
		delete judge;
	if (player2 != NULL)
		delete player2;
	if (bag != NULL)
		delete bag;
	if (dic != NULL)
		delete dic;
	if (heu != NULL)
		delete heu;
}

