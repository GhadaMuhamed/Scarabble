/*
 * Communcation.h
 *
 *  Created on: Nov 26, 2018
 *      Author: ghada
 */

#ifndef COMMUNICATION_COMMUNCATION_H_
#define COMMUNICATION_COMMUNCATION_H_
#include "../commToImp.h"
#include "../Board/Board.h"
#include "../Player/Player.h"
#include "../source.cpp"

class Communcation {
	Board* board;
	Player* player1;
	Player* player2;
	Judge* judge;
	Bag* bag;
	dictionary* dic;
	Heuristic* heu;
	Move myLast, hisLast;
public:
	Communcation();
	bool checkStrings(Move_to_from_server);
	impToInt start(intToImp msg);
	Move castToMove(Move_to_from_server&);
	Move_to_from_server castToServerMove(Move&);
	void addPlayerTies(uint8_t tiles[]);
	void applyOpponentMove(Move& mv, uint8_t tiles[]);

	virtual ~Communcation();
}
;
#endif /* COMMUNICATION_COMMUNCATION_H_ */
