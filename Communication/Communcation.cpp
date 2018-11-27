/*
 * Communcation.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: ghada
 */

#include "Communcation.h"

Communcation::Communcation() {
	// TODO Auto-generated constructor stub
	board = NULL;

}
void Communcation::start(commToImp c) {
	// start or disconnect
	if (c.Msgtype == 1 || c.Msgtype == 12) {
		board = new Board(c.Board_from_server);

	}
}

Communcation::~Communcation() {
	if (board != NULL)
		delete board;
	// TODO Auto-generated destructor stub
}

