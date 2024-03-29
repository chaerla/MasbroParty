#include "ReRoll.hpp"

void ReRoll::activate(Set &set)
{
    vector<CandyPlayer> &listOfPlayer = set.getListOfPlayers();
    int currPlayerIdx = set.getCurrPlayerIdx();
    cout << "Your cards are thrown away ...\n";

    // Ambil dua kartu baru
    vector<ColorCard> newPlayerDeck;
    ColorCard add1 = set.getMainDeck().getFromMainDeck();
    ColorCard add2 = set.getMainDeck().getFromMainDeck();

    // Set kartu player dengan dua kartu baru
    listOfPlayer[currPlayerIdx].setPlayerDeck(newPlayerDeck);
    listOfPlayer[currPlayerIdx].addPlayerCard(add1);
    listOfPlayer[currPlayerIdx].addPlayerCard(add2);

    cout << "You got two new cards:\n";
    ColorCard::printGroup(listOfPlayer[currPlayerIdx].getPlayerDeck());
    cout << endl;
}

string ReRoll::getCommandName()
{
    return "RE-ROLL";
}