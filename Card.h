// Card.h
#ifndef CARD_H
#define CARD_H

#include "agent.h"

struct Card {
    AgentType type;

    Card() = default;                // default constructor
    Card(AgentType t) : type(t) {}   // constructor با AgentType

    // مقایسه دو کارت بر اساس نوع ایجنت
    bool operator==(const Card& other) const {
        return type == other.type;
    }
};

#endif
