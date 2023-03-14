#include <bits/stdc++.h>
#include "Player.hpp"

using namespace std;

int Player::playerCount_ = 0;
Player::Player(string nickname) : nickname_(nickname), hasPlayed_(false), abilityStatus_(false)
{
    this->point_ = 0;
    playerCount_++;
    this->id_ = playerCount_;
    // To do: adding deck & ability
}

Player::Player(const Player &other)
{
    this->nickname_ = other.nickname_;
    this->point_ = other.point_;
    this->hasPlayed_ = other.hasPlayed_;
    this->ability_ = other.ability_;
    this->abilityStatus_ = other.abilityStatus_;
    this->deck = other.deck;
    playerCount_++;
    this->id_ = playerCount_;
    // To do: adding deck & ability
}

Player::~Player()
{
    playerCount_--;
}

void Player::setNickname(string nickname)
{
    this->nickname_ = nickname;
}

void Player::setPoint(int point)
{
    this->point_ = point;
}

void Player::addPoint(int pointVal)
{
    this->point_ += pointVal;
}

string Player::getNickname() const
{
    return this->nickname_;
}

int Player::getPoint() const
{
    return this->point_;
}

int Player::getPlayerCount()
{
    return playerCount_;
}

string Player::getAbility()
{
    return ability_;
}

void Player::removePlayerCard(ColorCard toRemove)
{
    (*this) - toRemove;
}

void Player::addPlayerCard(ColorCard toAdd)
{
    (*this) + toAdd;
}

vector<ColorCard> Player::getPlayerDeck()
{
    return this->deck;
}

void Player::setPlayerDeck(vector<ColorCard> playerDeck)
{
    this->deck = playerDeck;
}

float Player::getValue()
{
    return 0.0;
}

void Player::setAbility(string ability)
{
    this->ability_ = ability;
}

bool Player::getAbilityStatus()
{
    return this->abilityStatus_;
}

void Player::setAbilityStatus(bool status)
{
    this->abilityStatus_ = status;
}

void Player::setHasPlayed(bool hasPlayed)
{
    this->hasPlayed_ = hasPlayed;
}

bool Player::getHasPlayed()
{
    return this->hasPlayed_;
}

void Player::print()
{
    cout << nickname_ << endl;
    cout << "  Points: " << point_ << endl;
}

void Player::printCards()
{
    for (auto &c : this->deck)
    {
        c.printInfo();
    }
    ColorCard::printGroup(this->deck);
}

void Player::deleteMinValueFromCombo(vector<ColorCard> &combo, int limit)
{
    if (combo.size() == limit)
    {
        auto minVal = min_element(combo.begin(), combo.end(), Card::compareByValue);
        if (minVal != combo.end())
        {
            combo.erase(minVal);
        }
    }
}

void Player::deleteMinColorFromCombo(vector<ColorCard> &combo, int limit)
{
    if (combo.size() == limit)
    {
        auto minVal = min_element(combo.begin(), combo.end(), ColorCard::compareByColor);
        if (minVal != combo.end())
        {
            combo.erase(minVal);
        }
    }
}

Combo *Player::checkPlayerCombo(TableDeck tableDeck)
{
    return nullptr;
}

Flush *Player::checkPlayerFlush(TableDeck tableDeck)
{
    map<string, vector<ColorCard>> temp;
    // count the freq of each color in the table deck
    for (auto &c : tableDeck.getDeck())
    {
        temp[c.getColor()].push_back(c);
    }
    ColorCard firstCard = this->deck[0];
    deleteMinValueFromCombo(temp[firstCard.getColor()], 5);
    temp[firstCard.getColor()].push_back(firstCard);

    ColorCard secondCard = this->deck[1];
    if (secondCard.getColor() == firstCard.getColor())
    {
        if (secondCard.getValue() > min_element(temp[secondCard.getColor()].begin(), temp[secondCard.getColor()].end(), Card::compareByValue)->getValue() || temp[secondCard.getColor()].size() < 5)
        {
            deleteMinValueFromCombo(temp[secondCard.getColor()], 5);
            temp[secondCard.getColor()].push_back(secondCard);
        }
    }
    else
    {
        deleteMinValueFromCombo(temp[secondCard.getColor()], 5);
        temp[secondCard.getColor()].push_back(secondCard);
    }

    if (temp[firstCard.getColor()].size() == 5)
    {
        return new Flush(temp[firstCard.getColor()]);
    }

    if (temp[secondCard.getColor()].size() == 5)
    {
        return new Flush(temp[secondCard.getColor()]);
    }

    return nullptr;
}

FourOfAKind *Player::checkPlayerFourOfAKind(TableDeck tableDeck)
{
    map<int, vector<ColorCard>> temp;
    // count the freq of each color in the table deck
    for (auto &c : tableDeck.getDeck())
    {
        deleteMinColorFromCombo(temp[c.getValue()], 4);
        temp[c.getValue()].push_back(c);
    }

    ColorCard firstCard = this->deck[0];
    deleteMinColorFromCombo(temp[firstCard.getValue()], 4);
    temp[firstCard.getValue()].push_back(firstCard);

    ColorCard secondCard = this->deck[1];
    if (temp[secondCard.getValue()].size() == 4)
    {
        auto minVal = min_element(temp[secondCard.getValue()].begin(), temp[secondCard.getValue()].end(), ColorCard::compareByColor);
        if (minVal != temp[secondCard.getValue()].end())
        {
            temp[secondCard.getValue()].erase(minVal);
        }
    }
    temp[secondCard.getValue()].push_back(secondCard);

    if (temp[firstCard.getValue()].size() == 4)
    {
        return new FourOfAKind(temp[firstCard.getValue()]);
    }

    if (temp[secondCard.getValue()].size() == 4)
    {
        return new FourOfAKind(temp[secondCard.getValue()]);
    }

    return nullptr;
};

HighCard *Player::checkPlayerHighCard()
{
    HighCard *hc1 = new HighCard(this->deck[0]);
    HighCard *hc2 = new HighCard(this->deck[0]);
    if (hc1->getValue() > hc2->getValue())
    {
        delete hc2;
        return hc1;
    }
    delete hc1;
    return hc2;
};

Pair *Player::checkPlayerPair(TableDeck tableDeck)
{
    // sort ascending
    sort(this->deck.begin(), this->deck.end(), ColorCard::compareByValueThenColor);
    sort(tableDeck.getDeck().begin(), tableDeck.getDeck().end(), ColorCard::compareByValueThenColor);

    // check inner deck first
    bool playerPair = false;

    if (this->deck[0].getValue() == this->deck[1].getValue())
    {
        playerPair = true;
    }

    // loop through each card in deck
    for (auto c = this->deck.rbegin(); c != this->deck.rend(); ++c)
    {
        // check if c have pair in tableDeck
        for (auto d = tableDeck.getDeck().rbegin(); d != tableDeck.getDeck().rend(); ++d)
        {
            // if there is pair, return pair
            if (c->getValue() == d->getValue())
            {
                pair<ColorCard, ColorCard> cardPair;

                // check if inner deck is pair and inner deck pair is greater than this pair
                if (playerPair && !ColorCard::compareByColor(this->deck[0], *d))
                {
                    cardPair.first = this->deck[0];
                    cardPair.second = this->deck[1];
                }
                else
                {
                    // return this pair
                    cardPair.first = *c;
                    cardPair.second = *d;
                }

                return new Pair(cardPair);
            }
        }
    }
    return nullptr;
};

Straight *Player::checkPlayerStraight(TableDeck tableDeck){
    sort(this->deck.begin(), this->deck.end(), ColorCard::compareByValueThenColor);
    // insert decks to map
    map<int, vector<ColorCard>> decks;

    for (auto &c : tableDeck.getDeck()){
        decks[c.getValue()].push_back(c);
    }

    for (auto &c : this->deck){
        decks[c.getValue()].push_back(c);
    }

    int prev = -1;
    bool usedPlayer = false;
    vector<ColorCard> answer;
    // sort decks ascending
    while (decks.size() >= 5 && !usedPlayer){

        int high = decks.rbegin()->first;
        int prev = decks.rbegin()->first;
        for (auto it = decks.rbegin(); it != decks.rend(); ++it){   
            if (prev - it->first > 1){
                high = it->first;
                prev = it->first;
                answer.clear();
            }

            if (it->second.size() > 1) {
                sort(it->second.begin(), it->second.end(), ColorCard::compareByColor);
                answer.push_back(it->second[it->second.size()-1]);
            } else {
                answer.push_back(it->second[0]);
            }

            prev = answer.back().getValue();

            if (!usedPlayer){
                usedPlayer = (answer.back() == this->deck[0]) || (answer.back() == this->deck[1]);
            }

            if (high - it->first == 4){
                break;
            }
        }   

        if (answer.size() == 5){
            sort(answer.begin(), answer.end(), ColorCard::compareByValueThenColor);

            if (!usedPlayer){
                // try to change

                for (int i = 0; i <= 1; i++){
                    if (this->deck[i].getValue() <= high && this->deck[i].getValue() >= high-4){
                        int currentVal = this->deck[i].getValue();
                        auto it = std::find_if(answer.begin(), answer.end(), [currentVal](const ColorCard& card) {
                            return card.getValue() == currentVal;
                        });

                        if (it != answer.end()){
                            // then change
                            int idx = distance(answer.begin(), it);
                            answer[idx] = this->deck[i];
                            usedPlayer = true;
                            break;
                        }
                    }
                }
            } 

            if (usedPlayer){
                sort(answer.begin(), answer.end(), ColorCard::compareByValueThenColor);
                return new Straight(answer[0],answer[1],answer[2],answer[3],answer[4]);
            } else {
                decks.erase(decks.rbegin()->first);
                answer.clear();
            }
        }
    }

    return nullptr;
};

// StraightFlush* checkPlayerStraightFlush();

ThreeOfAKind *Player::checkPlayerThreeOfAKind(TableDeck tableDeck)
{
    map<int, vector<ColorCard>> temp;
    // count the freq of each color in the table deck
    for (auto &c : tableDeck.getDeck())
    {
        deleteMinColorFromCombo(temp[c.getValue()], 3);
        temp[c.getValue()].push_back(c);
    }

    ColorCard firstCard = this->deck[0];
    deleteMinColorFromCombo(temp[firstCard.getValue()], 3);
    temp[firstCard.getValue()].push_back(firstCard);

    ColorCard secondCard = this->deck[1];
    if (temp[secondCard.getValue()].size() == 3)
    {
        auto minVal = min_element(temp[secondCard.getValue()].begin(), temp[secondCard.getValue()].end(), ColorCard::compareByColor);
        if (minVal != temp[secondCard.getValue()].end())
        {
            temp[secondCard.getValue()].erase(minVal);
        }
    }
    temp[secondCard.getValue()].push_back(secondCard);

    if (temp[firstCard.getValue()].size() == 3)
    {
        return new ThreeOfAKind(temp[firstCard.getValue()]);
    }

    if (temp[secondCard.getValue()].size() == 3)
    {
        return new ThreeOfAKind(temp[secondCard.getValue()]);
    }

    return nullptr;
};

TwoPair *Player::checkPlayerTwoPair(TableDeck tableDeck)
{
    sort(this->deck.begin(), this->deck.end(), ColorCard::compareByValueThenColor);
    sort(tableDeck.getDeck().begin(), tableDeck.getDeck().end(), ColorCard::compareByValueThenColor);

    map<int, vector<ColorCard>> temp;
    vector<ColorCard> tableDeckPair;

    bool foundPair = false;
    int tableNum = -1;
    for (auto it = tableDeck.getDeck().rbegin(); it != tableDeck.getDeck().rend(); it++)
    {
        if (!foundPair && temp[it->getValue()].size() == 1)
        {
            temp[it->getValue()].push_back(*it);
            tableDeckPair = temp[it->getValue()];
            tableNum = it->getValue();
            foundPair = true;
        }
        if (!foundPair || temp.find(it->getValue()) == temp.end())
        {
            temp[it->getValue()].push_back(*it);
        }
    }

    pair<ColorCard, ColorCard> firstCardPair, secondCardPair;
    // check player Pair
    if (foundPair && deck[0].getValue() == deck[1].getValue())
    {
        firstCardPair.first = deck[0];
        firstCardPair.second = deck[1];
        secondCardPair.first = tableDeckPair[0];
        secondCardPair.second = tableDeckPair[1];
        return new TwoPair(firstCardPair, secondCardPair);
    }

    if (temp[deck[0].getValue()].size() == 1)
    {
        temp[deck[0].getValue()].push_back(deck[0]);
    }

    if (temp[deck[1].getValue()].size() == 1)
    {
        temp[deck[1].getValue()].push_back(deck[1]);
    }

    bool usedTablePair = false;
    int countPair = 0;
    bool usedFirstCardPair = false;

    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        int key = it->first;
        vector<ColorCard> value = it->second;
        if (value.size() == 2){
            bool insert = false;
            if (key != tableNum){
                insert = true;
            } else if (!usedTablePair){
                insert = true;
                usedTablePair = true;
            }

            if (insert){
                if (!usedFirstCardPair){
                    firstCardPair.first = value[0];
                    firstCardPair.second = value[1];
                    usedFirstCardPair = true;
                } else {
                    secondCardPair.first = value[0];
                    secondCardPair.second = value[1];
                    return new TwoPair(firstCardPair, secondCardPair);
                }
            }
        }
    }

    return nullptr;
};
