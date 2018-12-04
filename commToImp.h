#include<bits/stdc++.h>

struct Move_to_from_server {
	uint8_t column, row; //get values from 1 to 15
	uint8_t Directon; //Right=0, Down=1
	uint8_t tiles[7]; //this represents the tiles we will put as the new play on the board
					  //we get here from 1-26 representing from A to Z
					  //and get from 101 to 126 if we used the blank tile as A to Z
	int32_t scoreOfTheMove;					//expected score of the played move
};
struct intToImp {
	uint8_t Msgtype;//the actions we make to play, or the actions we get as reply from the server
	uint8_t order;//this variable holds 1 or 2, if we get 1 in it means we are the current player and if get 2 we are the other player
	uint8_t Board_from_server[15][15];
	Move_to_from_server move;
	int32_t Player_score, opponent_score;//we get these two from the srever, server updates our scores
};

struct impToInt {
	uint8_t Msgtype;
	uint8_t Board[15][15];
	Move_to_from_server move;
	uint8_t rack[7];
	bool boardUpdated;
	bool rackUpdated;
};

