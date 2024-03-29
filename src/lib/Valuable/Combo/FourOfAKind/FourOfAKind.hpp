#ifndef _FOUR_OF_A_KIND_HPP_
#define _FOUR_OF_A_KIND_HPP_

#include "../Combo.hpp"
#include <vector>
#include <algorithm>

class FourOfAKind : public Combo
{
private:
    vector<ColorCard> quad_;

public:
    /**
     * @brief Construct a new Four Of A Kind object
     *
     * @param cards
     */
    FourOfAKind(vector<ColorCard> cards);

    /**
     * @brief Destroy the Four Of A Kind object
     *
     */
    virtual ~FourOfAKind();

    /**
     * @brief Get the Value object
     *
     * @return float
     */
    float getValue() const;
    void print();
    string getComboName() const;
};

#endif