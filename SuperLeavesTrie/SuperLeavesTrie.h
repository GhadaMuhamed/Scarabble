//
// Created by riham on 01/12/18.
//

#ifndef SCARABBLE_SUPERLEAVESTRIE_H
#define SCARABBLE_SUPERLEAVESTRIE_H

#include <bits/stdc++.h>
#include "../Player/Player.h"
#include "../Move/Move.h"

using namespace std;

const int ALPHABET_SIZE = 27;
const double FLOAT_MAX = 10000.0;
// Trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node
    // represents end of a word
    double isEndOfWord = -FLOAT_MAX;
};

class SuperLeavesTrie {
    TrieNode* root = nullptr;


    TrieNode* getTrie() {
        return root;
    }

    // Returns new trie node (initialized to NULLs)
    struct TrieNode *getNode() {
        auto *pNode = new TrieNode;

        pNode->isEndOfWord = -FLOAT_MAX;

        for (auto &i : pNode->children)
            i = nullptr;

        return pNode;
    }

    void insert(string key, double leafValue) {
        struct TrieNode *pCrawl = root;

        for (int i : key) {
            if (!pCrawl->children[i])
                pCrawl->children[i] = getNode();

            pCrawl = pCrawl->children[i];
        }

        // mark last node as leaf
        pCrawl->isEndOfWord = leafValue;
    }

    // Returns keyValue(double) if key presents in trie, else
    // -1 (not found)
    double search(string key) {
        struct TrieNode *pCrawl = root;

        for (int i : key) {
            if (!pCrawl->children[i])
                return -1;

            pCrawl = pCrawl->children[i];
        }
        if (pCrawl != nullptr && pCrawl->isEndOfWord != -FLOAT_MAX)
            return pCrawl->isEndOfWord;
        else return -1;
    }

    bool loadSuperLeaves(const string &filename)
    {
        ifstream file(filename.c_str(), ios::in | ios::binary);

        if (!file.is_open())
        {
            cerr << "Could not open " << filename << " to load superleave heuristic" << endl;
            return false;
        }

        unsigned char leaveSize;
        char leaveBytes[16];
        unsigned char intValueInt;
        unsigned char intValueFrac;
        unsigned int intValue;

        while (!file.eof())
        {
            file.read((char*)(&leaveSize), 1);
            file.read(leaveBytes, leaveSize);
            file.read((char*)(&intValueFrac), 1);
            file.read((char*)(&intValueInt), 1);
            if (file.eof())
                break;
            intValue = (unsigned int)(intValueInt) * 256 + (unsigned int)(intValueFrac);
            string leave;
            for (char leaveByte : leaveBytes) {
                if (leaveSize == 0) {
                    break;
                } else if (leaveByte == 1) {
                    leaveByte = 26;
                } else if (leaveByte < 5) {
                    cout << "HOW???";
                } else leaveByte -= 5;
                leave += leaveByte;
                leaveSize--;
            }
            double value = (double (intValue) / 256.0) - 128.0;

            insert(leave, value);
        }

        file.close();
        return true;
    }

public:
    SuperLeavesTrie() {
        root = new TrieNode;
        loadSuperLeaves("/home/riham/Documents/Machine Inteligence/Scarabble/SuperLeavesTrie/superleaves");
    }

    double getFromHeuristic(Player p) {
        string player_s = p.getTieStr();
        for (auto& c: player_s) {
            c -= 'A';
        }
        return search(player_s);
    }

    Move getBest(vector<Move> moves) {
        Move best_move;
        double least_val = FLOAT_MAX;
        for (Move& move: moves) {
            string played_s = move.playedWord;
            for (auto& c: played_s) {
                c -= 'A';
            }
            move.heuristicValue = search(played_s);
            if (least_val > move.heuristicValue) {
                least_val = move.heuristicValue;
                best_move = move;
            }
        }
        return best_move;
    }

    vector<Move> getBest23(vector<Move> moves) {
        priority_queue<Move> best_moves;
        for (Move& move: moves) {
            string played_s = move.playedWord;
            for (auto& c: played_s) {
                c -= 'A';
            }
            move.heuristicValue = search(played_s);
            best_moves.push(move);
        }
        moves.clear();
        int cnt = 23;
        while (cnt--) moves.push_back(best_moves.top()), best_moves.pop();
        return moves;
    }
};


#endif //SCARABBLE_SUPERLEAVESTRIE_H
