#ifndef _FLUSH_HPP_
#define _FLUSH_HPP_

#include "../Combo.hpp"
#include <math.h>

class Flush : public Combo
{
private:
    vector<ColorCard> flushHand_;

public:
    /**
     * @brief Construct a new Flush object
     *
     */
    Flush(vector<ColorCard> cards);

    ~Flush();

    /**
     * @brief Get the Value object
     *
     * @return float
     */
    float getValue() const;

    void print();
};

#endif