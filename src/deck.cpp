#include "../include/deck.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <random>
#include <chrono>

void Deck::randomize()
{
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cards.begin(),cards.end(),std::default_random_engine(seed));
}

std::string Deck::getTop(bool turn)
{
        std::string value_string = std::to_string(static_cast<int>(cards[top]->value));
        if(value_string == "11") value_string = "Jack";
        if(value_string == "12") value_string = "Queen";
        if(value_string == "13") value_string = "King";
        if(value_string == "14") value_string = "Ace";
        std::map<Card::Card_Colour,std::string> StringValues = {                                                                              
                {Card::Card_Colour::Clubs, "Clubs ♣"},
                {Card::Card_Colour::Spades, "Spades ♠"},
                {Card::Card_Colour::Diamonds, "Diamonds ♦"},
                {Card::Card_Colour::Hearts, "Hearts ♥"},
        };

        std::string result = value_string + " of " + StringValues.find(cards[top]->colour)->second;               
        if (turn) {
                playerCardVal = cards[top]->getNumericalValue();
        }
        else AICardVal = cards[top]->getNumericalValue();
        top++;
        return result;
}
