#include "InventoryHolder.hpp"

template <class T>
InventoryHolder<T>::InventoryHolder() {}

template <class T>
InventoryHolder<T>::InventoryHolder(const InventoryHolder &other)
{
    for (auto elmt : other.deck)
    {
        this->deck.push_back(elmt);
    }
}

template <class T>
InventoryHolder<T>::~InventoryHolder()
{
    this->deck.clear();
}

template <class T>
InventoryHolder<T> &InventoryHolder<T>::operator+(const T &toAdd)
{
    this->deck.push_back(toAdd);
    return *this;
}

template <class T>
InventoryHolder<T> &InventoryHolder<T>::operator-(const T &toRemove)
{
    auto idxRemove = find(this->deck.begin(), this->deck.end(), toRemove);
    if (idxRemove != this->deck.end())
    {
        this->deck.erase(idxRemove);
    }
    return *this;
}

template <class T>
InventoryHolder<T> &InventoryHolder<T>::operator=(const InventoryHolder &other)
{
    if (this != &other)
    {
        this->deck.clear();
        this->deck = other.deck;
    }
    return *this;
}

template <class T>
vector<T> &InventoryHolder<T>::getDeck()
{
    return this->deck;
}

template class InventoryHolder<ColorCard>;
