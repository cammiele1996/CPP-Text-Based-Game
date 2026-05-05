#pragma once
#include <string>


// This class represents an item in the game world
// Some items are keys that are required the face the final boss
// Some items modify player stats


class Item {
    private:
        std::string name;        // Display name of the item
        std::string description; // Description of the item
        bool isRequired;         // Is item required for final boss?

    public:

		// Default constructor
		Item();

        // Constructor
        Item(std::string name, std::string description, bool isRequired);
        
        // Getters
        std::string getName() const;          // Returns the item name
        std::string getDescription() const;   // Returns the item description
        bool getIsRequired() const;           // Returns true if the item is required for the final boss
};
