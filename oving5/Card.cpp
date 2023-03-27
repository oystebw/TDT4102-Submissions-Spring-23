#include "Card.h"

string suitToString(Suit suit){
    switch (suit){
        case Suit::clubs: return "Clubs";
        case Suit::diamonds: return "Diamonds";
        case Suit::hearts: return "Hearts";
        case Suit::spades: return "Spades";
    }
}

string rankToString(Rank rank){
    switch (rank){
        case Rank::two: return "Two";
        case Rank::three: return "Three";
        case Rank::four: return "Four";
        case Rank::five: return "Five";
        case Rank::six: return "Six";
        case Rank::seven: return "Seven";
        case Rank::eight: return "Eight";
        case Rank::nine: return "Nine";
        case Rank::ten: return "Ten";
        case Rank::jack: return "Jack";
        case Rank::queen: return "Queen";
        case Rank::king: return "King";
        case Rank::ace: return "Ace";
    }
}