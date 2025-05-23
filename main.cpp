#include <array>
#include <stack>
#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <random>

enum class Suit {
    heart,
    diamond,
    club,
    spade,
    last
};

class Card {
public:
    
    Card() : value{1}, suit{Suit::club} {}

    Card(int val, Suit s) {
        value = val;
        suit = s;
    }

    Suit suit;
    int value;

    friend std::ostream &operator<<(std::ostream &os, const Card &card) { 

        os << "Card:\t";// << card.value << "\t Suit:\t\n";

        // switch (card.suit) {
        //     case Suit::club:
        //         os << "Club\n";
        //         break;
        //     case Suit::heart:
        //         os << "Heart\n";
        //         break;
        //     case Suit::spade:
        //         os << "Spade\n";
        //         break;
        //     case Suit::diamond:
        //         os << "Diamond\n";
        //         break;
        //     case Suit::last:
        //         break;
        // }
    }
};

class Deck {
public:
    Deck() : numCards{0} {};

    int numCards;

    std::vector<Card> cards;

    std::random_device rd;

    Card dealCard() {

        Card c = cards.back();
        cards.pop_back();
        numCards--;
        return c;
    };

    void shuffle() {

        std::mt19937 g(rd());
        
        std::shuffle(cards.begin(), cards.end(), g);

    };

    void init() {
        std::array<Suit, 4> suits = {Suit::club, Suit::diamond, Suit::heart, Suit::spade};
        for (int i = 1; i < 14; i++) {
            for (const auto& s : suits) {

                cards.push_back(Card{i, s});

                numCards++;
            }
        }
    

    }

    void singleInit() {
        cards.clear();
        init();
        shuffle();
    }

    void doubleInit() {
        
        cards.clear();
        init();
        init();
        shuffle();
    }

private:

};

class Hand {
public:

    std::vector<Card> cards;

    void addCard(Card c) {

        cards.push_back(c);

    }

};

class Player {

public:

    Hand hand;



};


int main() {

    Suit s = Suit::club;
    Deck deck;

    deck.doubleInit();

    std::cout << "Number of Cards in Deck:\t" << deck.numCards << std::endl;


    // int numCards = deck.numCards;
    // for (int i = 0; i < numCards; i++) {

    //     Card c = deck.dealCard();
    //     std::cout << "Card:\t " << c.value << "\tSuit:\t";
    //     switch (c.suit) {
    //         case Suit::club:
    //             std::cout << "Club\n";
    //             break;
    //         case Suit::heart:
    //             std::cout << "Heart\n";
    //             break;
    //         case Suit::spade:
    //             std::cout << "Spade\n";
    //             break;
    //         case Suit::diamond:
    //             std::cout << "Diamond\n";
    //             break;
    //         case Suit::last:
    //             break;
    //     }

    //     std::cout << "Num Cards:\t" << deck.numCards << std::endl;
    // }

    return 0;
}