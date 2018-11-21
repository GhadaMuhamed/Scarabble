//
// Created by riham on 24/10/18.
//

#include "Bag.h"

int Bag::bagLen() {
    return bagSize;
}

int Bag::removeTie(int index) {
    if (bag[index] == 0) return -1; // check that this char exists
    bag[index]--, bagSize--;
    return scores[index];
}
int Bag::addTie(int index) {
	bag[index]++, bagSize++;
	return scores[index];
}

int Bag::getTieCount(int index) {
    return bag[index];
}

int Bag::getTieScore(int index) {
    return scores[index];
}

Bag& Bag::operator=(Bag const& myObj) {
    bagSize = myObj.bagSize;
    memcpy(bag, myObj.bag, sizeof bag);
    return *this;
}

bool Bag::exchangeTie(int src, int dst) {
    if (removeTie(src) == -1) return false;
    bag[dst]++;
    return true;
}

// a friend function for printing the bag
ostream& operator<<(ostream& os, Bag const& myObj) {
    int cnt = 0;
    os << "Bag: ";
    for (int b: myObj.bag) {
        os << "( char=" << char(cnt+'A') << ", count=" << b << ", score=" << myObj.scores[cnt++] << " )\t";
    }
    return os << endl;
}
