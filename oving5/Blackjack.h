#pragma once
#include "CardDeck.h"

class Blackjack{
    private:
        CardDeck deck;
        vector<Card> playerHand;
        vector<Card> dealerhand;
        int playerHandSum;
        int dealerHandSum;
    public:
        int getCardValue(Card);
        int getHandScore(vector<Card>);
        bool askPlayerDrawCard();
        void drawPlayerCard();
        void drawDealerCard();
};

bool isAce(Card);