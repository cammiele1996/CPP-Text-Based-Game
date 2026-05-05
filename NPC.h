#pragma once
#include <string>

// This class represents a non-player character (NPC) in the game
// NPCs can interact with players and provide information or quests
// NPCs can also provide items or assistance

class NPC { 
    private:
        std::string name;           // The name of the NPC
        std::string description;    // A description of the NPC
        std::string dialogue;       // Dialogue text for the NPC

    public:
        
        // Constructor
        NPC(std::string name, std::string description, std::string dialogue);

        // Getters
        std::string getName() const;            // Retrieve the name of the NPC
        std::string getDescription() const;     // Retrieve the description of the NPC
        std::string getDialogue() const;        // Retrieve the dialogue text of the NPC

};
