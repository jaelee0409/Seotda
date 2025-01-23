#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

#include "game/Deck.h"
#include "game/Card.h"

Deck::Deck(SDL_Renderer* _renderer) : renderer(_renderer)
{
    initializeDeck();
}

void Deck::initializeDeck()
{
    fullDeck.push_back(new Card(CardSuit::January, CardType::Bright, renderer));
    fullDeck.push_back(new Card(CardSuit::January, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::February, CardType::Animal, renderer));
    fullDeck.push_back(new Card(CardSuit::February, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::March, CardType::Bright, renderer));
    fullDeck.push_back(new Card(CardSuit::March, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::April, CardType::Animal, renderer));
    fullDeck.push_back(new Card(CardSuit::April, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::May, CardType::DoubleJunk, renderer));
    fullDeck.push_back(new Card(CardSuit::May, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::June, CardType::Animal, renderer));
    fullDeck.push_back(new Card(CardSuit::June, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::July, CardType::Animal, renderer));
    fullDeck.push_back(new Card(CardSuit::July, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::August, CardType::Bright, renderer));
    fullDeck.push_back(new Card(CardSuit::August, CardType::Animal, renderer));
    fullDeck.push_back(new Card(CardSuit::September, CardType::DoubleJunk, renderer));
    fullDeck.push_back(new Card(CardSuit::September, CardType::Ribbon, renderer));
    fullDeck.push_back(new Card(CardSuit::October, CardType::Animal, renderer));
    fullDeck.push_back(new Card(CardSuit::October, CardType::Ribbon, renderer));

    reset();

    for (size_t i = 0; i < cards.size(); ++i) {
        cards[i]->setPosition(cards[i]->getPositionX() + i,cards[i]->getPositionY() - i); // 5 cards per row
    }
}

void Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card* Deck::deal()
{
    if (cards.empty()) {
        std::cerr << "No more cards in the deck!" << std::endl;
    }
    // Deal the top card (remove from the deck)
    Card* dealtCard = cards.back();
    cards.pop_back();
    return dealtCard;
}

void Deck::reset()
{
    cards = fullDeck;
    shuffle();
}

bool Deck::isEmpty() const
{
    return true;
}

void Deck::printDeck() const
{
    for (const Card* card : cards) {
        card->printCard();
    }
}

const std::vector<Card*>& Deck::getDeck() const
{
    return cards;
}
