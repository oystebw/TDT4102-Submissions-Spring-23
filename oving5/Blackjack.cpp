#include "Blackjack.h"

bool isAce(Card c){
    return c.getRank() == Rank::ace;
}

int Blackjack::getCardValue(Card card){
    if(card.getRank() == Rank::ace){
        return 11;
    }
    return static_cast<int>(card.getRank());
}

int Blackjack::getHandScore(vector<Card> hand){
    int total = 0;

    for(auto el: hand){
        total += getCardValue(el);
    }
    return total;
}

bool Blackjack::askPlayerDrawCard(){
    bool value;
    cout << "Do you want a new card? '0' for no and '1' for yes: ";
    cin >> value;
    return value;
}

void Blackjack::drawPlayerCard(){
    playerHand.push_back(deck.drawCard());
}

void Blackjack::drawDealerCard(){
    dealerhand.push_back(deck.drawCard());
}