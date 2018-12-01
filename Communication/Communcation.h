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
#include "../Judge/Judge.h"
#include "../Dictionary/dictionary.h"
#include "../Heuristic/Heuristic.h"

class Communcation {
	Board* board;
	Player* player1;
	Player* player2;
	Judge* judge;
	Bag* bag;
	dictionary* dic;
	Heuristic* heu;
public:
	Communcation();
	bool checkStrings(Move_to_from_server);
	void start(commToImp msg);
	Move castToMove(Move_to_from_server&);
	Move_to_from_server castToServerMove(Move&);

	virtual ~Communcation();
}
;

#endif /* COMMUNICATION_COMMUNCATION_H_ */
