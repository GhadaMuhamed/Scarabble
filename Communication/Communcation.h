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

class Communcation {
	Board* board;
public:
	Communcation();
	void start(commToImp msg);
	virtual ~Communcation();
};

#endif /* COMMUNICATION_COMMUNCATION_H_ */
