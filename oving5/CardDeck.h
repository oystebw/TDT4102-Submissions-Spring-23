#pragma once
#include "Card.h"

class CardDeck{
    private:
        vector<Card> cards;

        void swap(int, int);
    public:
        CardDeck();
        void print();
        void shuffle();
        Card drawCard();
};