#include "NPC.h"

using namespace std;

NPC::NPC(std::string name, std::string description, std::string dialogue) {
    this->name = name;
    this->description = description;
    this->dialogue = dialogue;
}

// --- Getters ---

std::string NPC::getName() const { return name; }
std::string NPC::getDescription() const { return description; }
std::string NPC::getDialogue() const { return dialogue; }