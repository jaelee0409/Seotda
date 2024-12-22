#include <algorithm>
#include <random>
#include <vector>

#include "game/Deck.h"
#include "game/Card.h"

Deck::Deck(SDL_Renderer* renderer) : renderer(renderer)
{
    cards.push_back(Card(CardSuit::January, CardType::Bright, renderer));
    cards.push_back(Card(CardSuit::January, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::February, CardType::Animal, renderer));
    cards.push_back(Card(CardSuit::February, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::March, CardType::Bright, renderer));
    cards.push_back(Card(CardSuit::March, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::April, CardType::Animal, renderer));
    cards.push_back(Card(CardSuit::April, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::May, CardType::DoubleJunk, renderer));
    cards.push_back(Card(CardSuit::May, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::June, CardType::Animal, renderer));
    cards.push_back(Card(CardSuit::June, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::July, CardType::Animal, renderer));
    cards.push_back(Card(CardSuit::July, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::August, CardType::Bright, renderer));
    cards.push_back(Card(CardSuit::August, CardType::Animal, renderer));
    cards.push_back(Card(CardSuit::September, CardType::DoubleJunk, renderer));
    cards.push_back(Card(CardSuit::September, CardType::Ribbon, renderer));
    cards.push_back(Card(CardSuit::October, CardType::Animal, renderer));
    cards.push_back(Card(CardSuit::October, CardType::Ribbon, renderer));

    printDeck();
}

void Deck::shuffle()
{
    // Use random_shuffle or better shuffling method
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::deal()
{
    // Deal the top card (remove from the deck)
    Card dealtCard = cards.back();
    cards.pop_back();
    return dealtCard;
}

void Deck::reset()
{
    // Clear the deck and re-populate it
    cards.clear();
}

bool Deck::isEmpty() const
{
    return true;
}

void Deck::printDeck() const
{
    for (const Card& card : cards) {
        card.printCard();
    }
}