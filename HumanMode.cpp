//
// Created by riham on 10/12/18.
//

#include <iostream>
#include <LearnedWeights/LearnedWeights.h>
#include "SuperLeavesTrie/SuperLeavesTrie.h"
#include "Bag/Bag.h"
#include "Board/Board.h"
#include "Player/Player.h"
#include "Judge/Judge.h"
#include "Simulate/simulate.h"
#include "Bstar/Bstar.h"
#include "Heuristic/Heuristic.h"
#include "Dictionary/dictionary.h"

void random_rack(Bag& bag, Player& player) {
    // set random rack for each player
    while (player.getTotalTies() < 7 && bag.bagLen() > 0) {
        int cur_rand = int((random() / (RAND_MAX + 1.0)) * 27);
        while (bag.getTieCount(cur_rand) == 0) {
            cur_rand = int((random() / (RAND_MAX + 1.0)) * 27);
        }
        bag.removeTie(cur_rand);
        player.addTie(cur_rand);
    }
}

Move appropriateSimulation(Board& board, dictionary& dic, Player players[2], int turn, simualte& sim, Heuristic& heu,
                           Judge  j, Bstar bstar,Bag & bag, vector<Move> &availableMoves ) {
    if (bag.bagLen() == 0) {
        node n = bstar.b_star(availableMoves, board, players[turn], players[1 - turn], bag, dic);
        return n.mv;
    } else {
        return sim.nextPlay(heu, availableMoves, board, bag, players[turn], j, players[1 - turn], 10);
    }
}

Move getHumanMoveGUI() {

    Move move = Move();
    // get move & check that this move is valid
    /*
     * move = GUI.getHumanMove();
     * while (!judge.isValidMove(move) {
     *  GUI.notValidMove();
     *  move = GUI.getHumanMove();
     * }
    */
    // gets human's move
    return move;
}

void sendBestMoveGUI(Move bestMove) {
    // send the best move of human player to the GUI
}

void sendMyMoveGUI(Move myMove) {
    // sends my move to GUI
}

int main() {
    Board board = Board();
    Bag bag = Bag();
    Player players[] = {Player(0), Player(1)};
    simualte sim = simualte();
    Bstar bstar = Bstar();
    dictionary dic = dictionary("/home/riham/Documents/Machine Inteligence/Scarabble/Dictionary/sowpods.txt");
    Judge judge = Judge();
    Heuristic heu = Heuristic(board, dic, bag, judge, players[0], players[1]);
    LearnedWeights learnedWeights = LearnedWeights();

    int turn = 0;
    int pass = 0;
    cout << "GAME BEGINS!\n";

    while (true) {
        random_rack(bag, players[turn]);
        string rack = players[turn].getTieStr();

        dic.execute(board, rack); // dictionary needs to handle first move on the board
        vector<Move> moves = dic.getVector();
        Move bestMove = appropriateSimulation(board, dic, players, turn, sim, heu, judge, bstar, bag, moves);
        if (bestMove.switchMove) {
            pass++;
        }
        else
            pass = 0;

        if (pass == 2) break;

        if (bestMove.tiles.empty()) // it's not exchange, apply move handles if it's switchMove
            if ( turn == 1 ) {
                // human's turn => then get the move from GUI
                Move humanMove = getHumanMoveGUI();

                players[turn].addScore(
                        judge.applyMove(humanMove, board, players[turn], bag)
                );

                sendBestMoveGUI(bestMove);
                learnedWeights.newMove(turn, humanMove, board, bag, judge);
            } else {// it's you turn => then play best move
                players[turn].addScore(
                        judge.applyMove(bestMove, board, players[turn], bag)
                );

                sendMyMoveGUI(bestMove);
                learnedWeights.newMove(turn, bestMove, board, bag, judge);
            }
        else {
            for (char tile : bestMove.tiles) {
                players[turn].playTie(tile - 'A');
            }
            random_rack(bag, players[turn]);
        }

        cout << board;
        cout << players[turn];
        cout << players[1 - turn];

        if (judge.isClosed(board)) {
            // send info about winner to learned weights
            if ( players[0].getScore() > players[1].getScore() ) {// wohooo we won
                learnedWeights.updateWeights(0);
            } else if (players[0].getScore() == players[1].getScore()) {
                learnedWeights.updateWeights(-1);
            } else learnedWeights.updateWeights(1);

            break;
        }

        turn = 1 - turn;
    }


    return 0;
}
