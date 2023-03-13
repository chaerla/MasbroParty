#include "Set.hpp"
#include <bits/stdc++.h>

using namespace std;

Set::Set()
{
}

Set::Set(vector<Player> &listOfPlayer, int firstPlayerIdx)
{
    this->listOfPlayer_ = listOfPlayer;
    this->points_ = 64;
    this->round_ = 1;
    this->mainDeck_ = MainDeck();
    this->tableDeck_ = TableDeck();
    this->firstPlayerIdx_ = firstPlayerIdx;
    this->currPlayerIdx = firstPlayerIdx;
}

Set::~Set()
{
    this->listOfPlayer_.clear();
}

void Set::setPoints(float multiplier)
{
    if (this->points_ == 1)
    {
        throw PointException();
    }
    this->points_ = this->points_ * multiplier;
    cout << this->points_;
}
void Set::printSetInfo()
{
    cout << "Current point for this set is " << points_ << endl;
    int ctr = 0;
    cout << "Current turn: " << endl;
    while (ctr < listOfPlayer_.size())
    {
        cout << "[" << ctr + 1 << "] ";
        listOfPlayer_[((ctr + getCurrPlayerIdx()) % listOfPlayer_.size())].print();
        ctr++;
    }
}

vector<Player> &Set::getListOfPlayers()
{
    return this->listOfPlayer_;
}

int Set::getFirstPlayerIdx()
{
    return this->firstPlayerIdx_;
}

int Set::getCurrPlayerIdx() const
{
    return this->currPlayerIdx;
}

MainDeck &Set::getMainDeck()
{
    return this->mainDeck_;
}

void Set::setMainDeck(MainDeck mainDeck)
{
    this->mainDeck_ = mainDeck;
}
