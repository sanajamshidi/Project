#include "deck.h"

void Deck::removeFromGame(const Card& card)
{
    drawPile.removeOne(card);
    discardPile.removeOne(card);
    removedPile.append(card);
}

void Deck::initialize(const QString& owner) {
    Q_UNUSED(owner);
    cards.clear();
    for(int i=0; i<4; i++) cards.append(Card(AgentType::Scout));
    for(int i=0; i<3; i++) cards.append(Card(AgentType::Sniper));
    for(int i=0; i<3; i++) cards.append(Card(AgentType::Sergeant));
}

void Deck::shuffle() {
    // engine واقعی بساز
    std::random_device rd;
    std::mt19937 g(rd()); // Mersenne Twister engine

    std::shuffle(cards.begin(), cards.end(), g); // استفاده از engine واقعی
}


bool Deck::isEmpty() const {
    return cards.isEmpty();
}

Card Deck::drawCard() {
    if(cards.isEmpty()) return Card(AgentType::Scout); // fallback
    return cards.takeFirst();
}

int Deck::remaining() const {
    return cards.size();
}
