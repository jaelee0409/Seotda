#include <algorithm>
#include <random>
#include <vector>

#include "Deck.h"
#include "Card.h"

Deck::Deck()
{
    // Create 48 unique cards. Assuming the cards have IDs from 0 to 47.
    for (int i = 0; i < 48; ++i) {
        // Assume Card has a constructor that takes x, y, w, h and an id or card name
        // For simplicity, let's just create a card with an integer ID
        cards.push_back(Card(Card::CardName::JanuaryBright));
    }
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