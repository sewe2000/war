#pragma once
#include "card.hpp"
#include <random>
#include <functional>
#include <array>

class Deck
{
public:
        Deck()
        {
                int it = 0;
               for (int i = 2; i <= 14; i++) {
                       for (int j = 0; j < 4; j++, it++) {
                        cards[it] = new Card(static_cast<Card::Card_Value>(i), static_cast<Card::Card_Colour>(j));
                       }
               }
               playersCards = 0;
               AIsCards = 0;
        }
        ~Deck()
        {
                for (int i = 0; i < 52; i++) {
                        delete cards[i];
                }
        }
        void randomize();
        std::string getTop(bool turn);
        int getPlayerVal() {return playerCardVal;}
        int getAIVal() {return AICardVal;}
        short getPlayersCards() {return playersCards;}
        short getAIsCards() {return AIsCards;}
        void changePlayersCards(unsigned short value) {playersCards += value;}
        void changeAIsCards(unsigned short value) {AIsCards += value;}
private:
        std::array<Card*,52>cards;
        short top = 0;
        short playerCardVal = 0, AICardVal = 0;
        short playersCards, AIsCards;
};
