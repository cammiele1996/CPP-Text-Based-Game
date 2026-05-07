#pragma once
#include <string>

// Represents a non-player character in the game.
// NPCs have static dialogue for now — quest-state aware dialogue is planned.

class NPC {
private:
    std::string name;
    std::string description; // Shown when the player searches the room
    std::string dialogue;    // Shown when the player talks to the NPC

public:

    // Constructor
    NPC(std::string name, std::string description, std::string dialogue);

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    std::string getDialogue() const;
};