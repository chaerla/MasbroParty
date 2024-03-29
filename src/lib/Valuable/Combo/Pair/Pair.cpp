#include "Pair.hpp"
using namespace std;

Pair::Pair(){
    
}
Pair::Pair(pair<ColorCard,ColorCard> cardPair):cardPair_(cardPair){

}

Pair::~Pair()
{
}

float Pair::getValue() const
{
    float res = HIGH_CARD_MAX;

    res += (0.05 * max(cardPair_.first.getBaseValue(), cardPair_.second.getBaseValue()) + 0.2 * cardPair_.first.getValue()); /* highest color in pair */

    return res;
}

void Pair::print()
{
    ColorCard::printGroup(this->cardPair_);
}

pair<ColorCard, ColorCard> Pair::getPair()
{
    return this->cardPair_;
}

string Pair::getComboName() const{
    return "PAIR";
}