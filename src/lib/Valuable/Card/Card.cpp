#include "Card.hpp"

Card::Card()
{

}

Card::Card(int value)
{
    value_ = value;
}

Card::~Card(){
    
}

bool Card::compareByValue(const Card & first, const Card & second) {
    return first.getValue() <= second.getValue();
}
