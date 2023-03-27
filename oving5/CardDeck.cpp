#include "CardDeck.h"

CardDeck::CardDeck(){
    for(int suit{0}; suit < 4; suit++){
        for(int rank{2}; rank < 15; rank++){
            Suit s = static_cast<Suit>(suit);
            Rank r = static_cast<Rank>(rank);
            cards.emplace_back(s, r);
        }
    }
}

void CardDeck::swap(int a, int b){
    assert(a >= 0 && b >= 0);
    assert(a < cards.size() && b < cards.size());

    Card res = cards[a];
    cards[a] = cards[b];
    cards[b] = res;
}

void CardDeck::print(){
    for(int idx{0}; idx < cards.size(); idx++){
        cout << cards[idx].toString() << '\n';
    }
}

void CardDeck::shuffle(){
    int a;
    int b;
    int size = cards.size() - 1;
    for(int x{0}; x < 1000; x++){
        a = randint(size);
        b = randint(size);
        swap(a, b);
    }
}

Card CardDeck::drawCard(){
    Card toBeReturned = cards.back();
    cards.pop_back();
    return toBeReturned;
}