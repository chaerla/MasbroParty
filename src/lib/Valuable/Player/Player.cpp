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
    this->abilityStatus_ = other.abilityStatus_;
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

ColorCard Player::getFromPlayer()
{
    ColorCard toRemove = this->deck.back();
    // (*this) - toRemove;
    return toRemove;
}

string Player::getAbility()
{
    return ability_;
}

void Player::addPlayerCard(ColorCard toAdd)
{
    // (*this) + toAdd;
}

void Player::addPlayerCard(MainDeck &mainDeck_)
{
    ColorCard toAdd = mainDeck_.getFromMainDeck();
    // (*this) + toAdd;
}

float Player::getValue()
{
    return 0.0;
}

void Player::setAbility(string ability)
{
    this->ability_ = ability;
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