#pragma once
#include <string>

// Represents an item in the game world.
// Items can be required for the final boss fight, required for a quest, or neither (decoys/flavor).

class Item {
private:
    std::string name;
    std::string description;
    bool isRequired;         // Must have this item to face the dragon
    bool isRequiredForQuest; // Required to progress a quest chain

public:

    // Default constructor — creates an empty placeholder item
    Item();

    // Constructor
    Item(std::string name, std::string description, bool isRequired, bool isRequiredForQuest);

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    bool getIsRequired() const;          // True if needed for the final boss
    bool getIsRequiredForQuest() const;  // True if needed for a quest

    // Setters
    void setIsRequiredForQuest(bool isRequiredForQuest);
    // void setIsRequired(bool isRequired); // Uncomment if boss requirements need to change at runtime
};