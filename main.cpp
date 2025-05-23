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
    joker,
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

    friend bool operator<(const Card& l, const Card& r)
    {
        return l.value < r.value;
    }

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

        return os;
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

        Card joker{0, Suit::joker};
        
        cards.push_back(joker);
        numCards++;
        cards.push_back(joker);
        numCards++;

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


    void sort() {
        std::sort(cards.begin(), cards.end());
    }
};

class Player {

public:

    Hand hand;

    Deck* deck;
    Player* nextPlayer;

    void setDeck(Deck* d) {
        deck = d;
    }

    void setNextPlayer(Player* p) {
        nextPlayer = p;
    }

    void draw() {
        hand.addCard(deck->dealCard());
        hand.addCard(deck->dealCard());
        hand.sort();

    }

    void printHand() {

        int i = 0;
        for (const auto& card : hand.cards) {

            std::cout << "Card " << i << ": " << card.value << " ";

            switch (card.suit) {
                case Suit::club:
                    std::cout << "Club\n";
                    break;
                case Suit::heart:
                    std::cout << "Heart\n";
                    break;
                case Suit::spade:
                    std::cout << "Spade\n";
                    break;
                case Suit::diamond:
                    std::cout << "Diamond\n";
                    break;
                case Suit::joker:
                    std::cout << "Joker\n";
                    break;
                case Suit::last:
                    break;

            
        }
         i++;
        }
    }

};

class Pack {
public:

    std::vector<Card> cards;

    
    void addCard(Card c) {

        cards.push_back(c);

    }
    
};

class Canasta {
public:

    Deck deck;
    Pack pack;

    std::array<Player, 4> players;
    
    Player* activePlayer;

    

    bool gameStarted = false;

    void startGame() {
        
        deck.doubleInit();

        int y = 1;
        for (auto& player : players) {

            for (int i = 0; i < 11; i++) {
                player.hand.addCard(deck.dealCard());
            }

            player.hand.sort();

            // Player 1 -> Player 2 [1]
            // Player 2 -> Player 3 [2]
            // Player 3 -> Player 4 [3]
            // Player 4 -> Player 1 [0]

            player.setDeck(&deck);

            player.setNextPlayer(&players[y % 4]);
            y++;
        }

        pack.addCard(deck.dealCard());

        activePlayer = &players[0];
        gameStarted = true;
    }

    void checkDeck() {
        if (deck.numCards <= 0) {
            gameStarted = false;
        }
    }

    void turn() {

        activePlayer->printHand();

        activePlayer->draw();

        activePlayer = activePlayer->nextPlayer;
        
        std::cout << "Num Cards:\t" << deck.numCards << std::endl;

        int x = 0;
        std::cin >> x; 
    }


};


int main() {

    Canasta canasta;

    canasta.startGame();

    std::cout << Card{0, Suit::joker} <<std::endl;

    while (canasta.gameStarted) {

        canasta.turn();


        canasta.checkDeck();
    }
    
    return 0;
}
