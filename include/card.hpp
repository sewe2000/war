#pragma once

class Card
{
public:
        enum Card_Colour
        {
                Clubs = 0,
                Diamonds = 1,
                Hearts = 2,
                Spades = 3
        };
        enum Card_Value
        {
                two = 2,three = 3,four = 4,five = 5,six = 6,seven = 7,eight = 8,nine = 9,ten = 10,
                Jack = 11, Queen = 12, King = 13, Ace = 14
        };
        Card(const Card_Value v, const Card_Colour c): colour{c}, value{v}
        {};
        int getNumericalValue()
        {
                return static_cast<int>(value);
        }
private:
        const Card_Colour colour;
        const Card_Value value;
        friend class Deck;
};
