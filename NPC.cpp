#include "NPC.h"

using namespace std;

// Constructor
NPC::NPC(std::string name, std::string description, std::string dialogue) {
    this->name = name;
    this->description = description;
    this->dialogue = dialogue;
}

// Getters

// Returns the name of the NPC
std::string NPC::getName() const {
    return name;
}

// Returns the description of the NPC
std::string NPC::getDescription() const {
    return description;
}

// Returns the dialogue text of the NPC
std::string NPC::getDialogue() const {
    return dialogue;
}
